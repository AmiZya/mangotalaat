#include "itempropertiesdialog.h"
#include "ui_itempropertiesdialog.h"

#include "database/databasemanager.h"
#include "model/additionals.h"
#include "model/component.h"
#include "model/itemdetail.h"

ItemPropertiesDialog::ItemPropertiesDialog(int aItemDetialId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemPropertiesDialog)
{
    ui->setupUi(this);
    this->itemDetialId = aItemDetialId;

    fillComponentsAndAdditionals();
}

ItemPropertiesDialog::~ItemPropertiesDialog()
{
    delete ui;
}

void ItemPropertiesDialog::on_buttonBox_accepted()
{
    this->isCancel = false;
    this->hide();
}

void ItemPropertiesDialog::on_buttonBox_rejected()
{
    this->isCancel = true;
    this->hide();
}

void ItemPropertiesDialog::fillComponentsAndAdditionals() {
    Database::DatabaseManager database;

    std::vector<Additionals> additionals = database.getAllAdditionals();
    std::vector<Component> components = database.getAllCompnents();

    Model::ItemDetail itemDetial = database.getItemDetailById(this->itemDetialId);
    std::vector<Component> currentComponentInItem = database.getCompnentsInItem(itemDetial.getItemId());

    // fill item description
    Model::Item item = database.getItemById(itemDetial.getItemId());
    QString sizeDescription = database.getItemSizeDescription(itemDetial.getSizeId(), database.ARABIC);
    this->ui->orderLineEdit->setText(item.getArabicName() + " - " + sizeDescription);

    // fill all additionals
    for(std::vector<Additionals>::iterator p= additionals.begin();
            p != additionals.end(); ++p) {
        QString name = p->getArabicName();
        this->ui->allAdditionalListWidget->addItem(name);
    }

    // fill all components
    for(std::vector<Component>::iterator p= components.begin();
            p != components.end(); ++p) {
        QString name = p->getArabicName();
        this->ui->allComponentsListWidget->addItem(name);
    }

    // fill current item components
    for(std::vector<Component>::iterator p= currentComponentInItem.begin();
            p != currentComponentInItem.end(); ++p) {
        QString name = p->getArabicName();
        this->ui->currentComponentsListWidget->addItem(name);
    }
}
