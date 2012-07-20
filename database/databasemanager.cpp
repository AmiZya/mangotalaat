#include "databasemanager.h"

namespace Database
{
    DatabaseManager::DatabaseManager()
    {
        database = QSqlDatabase::database();
        database.open();
    }

    DatabaseManager::~DatabaseManager()
    {
        database.close();
    }

    std::vector<Category> DatabaseManager::getCategories()
    {
        std::vector<Category> categories;

        QSqlQuery query("SELECT * FROM categories");
        while(query.next()) {
            int id = query.value(0).toInt();
            QString arabicName = query.value(1).toString();
            QString englishName = query.value(2).toString();

            Category category(id, arabicName, englishName);
            categories.push_back(category);
        }

        return categories;
    }

    std::vector<Item> DatabaseManager::getItemsInCategory(int categoryId)
    {
        std::vector<Item> items;
        QSqlQuery query(QString("SELECT * FROM items WHERE categories_id = %1").arg(categoryId));

        while(query.next()) {
            int id = query.value(0).toInt();
            QString arabicName = query.value(1).toString();
            QString englishName = query.value(2).toString();
            int categoryId = query.value(3).toInt();

            Item item(id, arabicName, englishName, categoryId);
            items.push_back(item);
        }

        return items;
    }

    std::vector<ItemDetail> DatabaseManager::getItemDetails(int itemId)
    {
        std::vector<ItemDetail> itemDetails;

        QSqlQuery query(QString("SELECT * FROM item_details WHERE item_id = %1").arg(itemId));
        while(query.next()) {
            int id = query.value(0).toInt();
            int itemId = query.value(1).toInt();
            int sizeId = query.value(2).toInt();
            int price = query.value(3).toInt();

            ItemDetail itemDetail = ItemDetail(id, itemId, sizeId, price);
            itemDetails.push_back(itemDetail);
        }

        return itemDetails;
    }

    ItemDetail DatabaseManager::getItemDetailById(int itemDetialId)
    {
        ItemDetail itemDetail;

        QSqlQuery query(QString("SELECT * FROM item_details WHERE id = %1").arg(itemDetialId));
        while(query.next()) {
            int id = query.value(0).toInt();
            int itemId = query.value(1).toInt();
            int sizeId = query.value(2).toInt();
            int price = query.value(3).toInt();

            itemDetail = ItemDetail(id, itemId, sizeId, price);
            break;
        }

        return itemDetail;
    }

    Item DatabaseManager::getItemById(int itemId) {
        Item item;

        QSqlQuery query(QString("SELECT * FROM items WHERE id = %1").arg(itemId));
        while(query.next()) {
            int id = query.value(0).toInt();
            QString arabicName = query.value(1).toString();
            QString englishName = query.value(2).toString();
            int categoryId = query.value(3).toInt();

            item = Item(id, arabicName, englishName, categoryId);
        }

        return item;
    }

    std::vector<Component> DatabaseManager::getAllCompnents()
    {
        std::vector<Component> components;

        QSqlQuery query(QString("SELECT * FROM components"));
        while(query.next()){
            int id = query.value(0).toInt();
            QString arabicName = query.value(1).toString();
            QString englishName = query.value(2).toString();

            Component component(id, arabicName, englishName);
            components.push_back(component);
        }

        return components;
    }

    std::vector<Component> DatabaseManager::getCompnentsInItem(int itemId)
    {
        std::vector<Component> components;

        QSqlQuery query(QString("SELECT * FROM item_components WHERE item_id = %1").arg(itemId));
        while(query.next()){
            int componentId = query.value(2).toInt();
            components.push_back(getComponentById(componentId));
        }

        return components;
    }

    Component DatabaseManager::getComponentById(int componentId)
    {
        Component component;

        QSqlQuery query(QString("SELECT * FROM components WHERE id = %1").arg(componentId));
        while(query.next()) {
            int id = query.value(0).toInt();
            QString arabicName = query.value(1).toString();
            QString englishName = query.value(2).toString();

            component = Component(id, arabicName, englishName);
        }

        return component;
    }

    Additionals DatabaseManager::getAdditionalsById(int additionalsId)
    {
        Additionals additionals;

        QSqlQuery query(QString("SELECT * FROM additionals WHERE id = %1").arg(additionalsId));
        while(query.next()) {
            int id = query.value(0).toInt();
            QString arabicName = query.value(1).toString();
            QString englishName = query.value(2).toString();
            int price = query.value(3).toInt();

            additionals = Additionals(id, arabicName, englishName, price);
            break;
        }

        return additionals;
    }

    std::vector<Additionals> DatabaseManager::getAllAdditionals()
    {
        std::vector<Additionals> additionals;

        QSqlQuery query(QString("SELECT * FROM additionals"));
        while(query.next()){
            int id = query.value(0).toInt();
            QString arabicName = query.value(1).toString();
            QString englishName = query.value(2).toString();
            int price = query.value(3).toInt();

            Additionals additional(id, arabicName, englishName, price);
            additionals.push_back(additional);
        }

        return additionals;
    }

    QString DatabaseManager::getItemSizeDescription(int sizeId, LAGNUAGE language) {
        QString result = "";

        QSqlQuery query(QString("SELECT * FROM item_size WHERE id = %1").arg(sizeId));
        while(query.next()) {
            //int id = query.value(0).toInt();
            QString arabicName = query.value(1).toString();
            QString englishName = query.value(2).toString();

            if ( language == ARABIC ) {
                result = arabicName;
            }
            else {
                result = englishName;
            }
        }

        return result;
    }

    bool DatabaseManager::addOrder(QDateTime currentTime, int orderTypeId, int cash,
                                   int discount, int totalCash, QList<Model::Order> orders) {
        QSqlQuery query(QString("INSERT INTO orders(order_time, order_type_id, cash, discount, total_cash, is_cancelled) VALUES(%1, %2, %3, %4, %5, %6")
                .arg(currentTime.toString()).arg(orderTypeId).arg(cash).arg(discount).arg(totalCash).arg(0));

        bool ret = query.exec();
        qDebug() << query.lastError();

        if ( ret ) {
            int orderId = query.lastInsertId().toInt();

            foreach(Model::Order order, orders) {
                QSqlQuery tmpQuery(QString("INSERT INTO order_details(order_id, item_detial_id, quantity, components_ids, additionals_ids, sugar, cash) VALUES(%1, %2, %3, %4, %5, %6, %7")
                    .arg(orderId).arg(order.getItemDetialId()).arg(order.getQunatity()).arg(fromListToText(order.getComponentsIds()))
                    .arg(fromListToText(order.getAdditionalsIds())).arg(order.getSugar()).arg(order.getCash()));

                tmpQuery.exec();
            }
        }

        return ret;
    }

    QString DatabaseManager::fromListToText(QStringList ids) {
        QString commaSeparatedId = "";

        for(int i=0; i<ids.size(); i++) {
            commaSeparatedId += ids.at(i);

            if ( i < ids.size() - 1 ) {
                commaSeparatedId += ",";
            }
        }

        return commaSeparatedId;
    }

    QStringList DatabaseManager::fromTextToList(QString text) {
        return text.split(",");
    }
}
