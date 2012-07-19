#include "itempropertiesdialog.h"
#include "ui_itempropertiesdialog.h"

#include "database/databasemanager.h"
#include "model/additionals.h"
#include "model/component.h"
#include "model/itemdetail.h"

ItemPropertiesDialog::ItemPropertiesDialog(Model::Order aOrder, bool newOrder, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemPropertiesDialog),
    order(aOrder)
{
    ui->setupUi(this);
    this->isNewOrder = newOrder;

    fillAllComponentsAndAdditionals();
    fillItemDescription();

    if ( newOrder )
        fillDefualtCurrentComponentsAndAdditionals();
    else
        fillCurrentOrderComponentsAndAdditionals();
}

ItemPropertiesDialog::~ItemPropertiesDialog()
{
    delete ui;
}

void ItemPropertiesDialog::on_buttonBox_accepted()
{
    // build modified order here
    QStringList newComponentsList = getNewComponentList();
    QStringList newAdditionalsList = getNewAdditionalList();
    QString sugar = getSugar();
    int quantity = 1;

    this->modifiedOrder = Model::Order(this->order.getItemDetialId(), quantity, newComponentsList, newAdditionalsList);

    this->isCancel = false;
    this->hide();
}

QStringList ItemPropertiesDialog::getNewComponentList() {
    QStringList componentList;

//    foreach(QListWidgetItem *item, ui->currentComponentsListWidget->items) {
//        componentList.append(item->text());
//    }

    return componentList;
}

QStringList ItemPropertiesDialog::getNewAdditionalList() {
    QStringList additionalList;

//    foreach(QListWidgetItem *item, ui->currentAdditionalListWidget->items) {
//        additionalList.append(item->text());
//    }

    return additionalList;
}

QString ItemPropertiesDialog::getSugar() {
    return "";
}

void ItemPropertiesDialog::on_buttonBox_rejected()
{
    this->isCancel = true;
    this->hide();
}

void ItemPropertiesDialog::fillDefualtCurrentComponentsAndAdditionals() {
    Database::DatabaseManager database;
    Model::ItemDetail itemDetial = database.getItemDetailById(this->order.getItemDetialId());
    std::vector<Component> currentComponentInItem = database.getCompnentsInItem(itemDetial.getItemId());

    for(std::vector<Component>::iterator p= currentComponentInItem.begin();
            p != currentComponentInItem.end(); ++p) {
        QString name = p->getArabicName();
        this->ui->currentComponentsListWidget->addItem(name);
    }
}

void ItemPropertiesDialog::fillCurrentOrderComponentsAndAdditionals() {
    Database::DatabaseManager database;
    QStringList componentsList = this->order.getComponentsIds();
    foreach(QString componentId, componentsList) {
        Component component = database.getComponentById(componentId.toInt());
        this->ui->currentComponentsListWidget->addItem(component.getArabicName());
    }

    QStringList additionalsList = this->order.getAdditionalsIds();
    foreach(QString additionalId, additionalsList) {
        Additionals additional = database.getAdditionalsById(additionalId.toInt());
        this->ui->currentAdditionalListWidget->addItem(additional.getArabicName());
    }
}

void ItemPropertiesDialog::fillItemDescription() {
    Database::DatabaseManager database;

    Model::ItemDetail itemDetial = database.getItemDetailById(this->order.getItemDetialId());
    Model::Item item = database.getItemById(itemDetial.getItemId());
    QString sizeDescription = database.getItemSizeDescription(itemDetial.getSizeId(), database.ARABIC);
    this->ui->orderLineEdit->setText(item.getArabicName() + " - " + sizeDescription);
}

void ItemPropertiesDialog::fillAllComponentsAndAdditionals() {
    Database::DatabaseManager database;

    std::vector<Additionals> additionals = database.getAllAdditionals();
    std::vector<Component> components = database.getAllCompnents();

    for(std::vector<Additionals>::iterator p= additionals.begin();
            p != additionals.end(); ++p) {
        QString name = p->getArabicName();
        this->ui->allAdditionalListWidget->addItem(name);
    }

    for(std::vector<Component>::iterator p= components.begin();
            p != components.end(); ++p) {
        QString name = p->getArabicName();
        this->ui->allComponentsListWidget->addItem(name);
    }
}
