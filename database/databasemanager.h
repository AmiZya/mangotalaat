#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QtSql>
#include <QString>
#include <vector>

#include "model/category.h"
#include "model/item.h"
#include "model/component.h"
#include "model/itemdetail.h"
#include "model/additionals.h"
#include "model/orderdetail.h"

#include "report/login.h"
#include "report/order.h"

using namespace Model;

namespace Database
{
    class DatabaseManager
    {
    public:
        DatabaseManager();
        ~DatabaseManager();

        std::vector<Item> getItemsInCategory(int categoryId);
        std::vector<Component> getCompnentsInItem(int itemId);
        std::vector<ItemDetail> getItemDetails(int itemId);

        std::vector<Category> getCategories();
        std::vector<Component> getAllCompnents();
        std::vector<Additionals> getAllAdditionals();

        Item getItemById(int itemId);
        ItemDetail getItemDetailById(int itemDetialId);
        QList<OrderDetail> getOrderDetailByOrderId(int orderId);
        Component getComponentById(int componentId);
        Additionals getAdditionalsById(int additionalsId);

        enum LAGNUAGE { ARABIC, ENGLISH };
        QString getItemSizeDescription(int sizeId, LAGNUAGE language);

        bool addOrder(QDateTime currentTime, int orderTypeId, int cash, int discount, int totalCash, QList<Model::OrderDetail> orders);
        bool cancelOrder(int orderId);

        bool closeTodayOrders(QDateTime time);
        bool addLoginEventLogging(int userId, QDateTime time, int eventType); // 1 login, 2 logout

        User getUserById(int id);
        QList<Login> getLoginReport(QDateTime from, QDateTime to);
        QList<Order> getOrderReport(QDateTime from, QDateTime to);
        QList<QDateTime> getCheckoutTimes();

    private:
        QString fromListToText(QStringList ids);
        QStringList fromTextToList(QString text);

    private:
        QSqlDatabase database;
    };
}

#endif // DATABASEMANAGER_H
