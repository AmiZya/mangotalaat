#include <QDebug>

#include "categorieswidget.h"
#include "database/databasemanager.h"

CategoriesWidget::CategoriesWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setObjectName("categoryWidget");
    this->signalMapper = new QSignalMapper(this);
    this->horizontalGroupBox = new QGroupBox(tr("Categories"));
    this->layout = new QGridLayout;

    this->horizontalGroupBox->setLayout(layout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(horizontalGroupBox);
    this->setLayout(mainLayout);

    connect(this->signalMapper, SIGNAL(mapped(int)), this, SLOT(setCurrentCategory(int)));

    this->createCategories();

}

CategoriesWidget::~CategoriesWidget()
{
}

void CategoriesWidget::createCategories()
{
    // Remove pervious buttons from grid layout
    this->removeCategories();

    // get all categories
    Database::DatabaseManager databaseManager;
    std::vector<Category> categories = databaseManager.getCategories();

    int i=0, col = 0, row = 1;
    for(std::vector<Category>::iterator p = categories.begin();
            p != categories.end(); ++p ) {

        buttons[i] = new QPushButton(p->getEnglishName());
        buttons[i]->setObjectName(QString("%1_CategoryButton").arg(p->getId()));
        connect(buttons[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        this->signalMapper->setMapping(buttons[i], p->getId());
        layout->addWidget(buttons[i], row, col);

        col++;
        i++;

        if ( col % ButtonsPerLine == 0) {
            row++;
            col = 0;
        }
    }
}

void CategoriesWidget::setCurrentCategory(int id){
    QString buttonName = QString::number(id) + "_CategoryButton";
    QList<QPushButton*> buttons = this->findChildren<QPushButton*>();
    foreach (QPushButton* button,buttons) {
        if (button->objectName() == buttonName)
            button->setChecked(true);
        else
            button->setChecked(false);
    }

    emit selectCategory(id);
}

void CategoriesWidget::removeCategories()
{
    QLayoutItem* item;
    while ((item = this->layout->takeAt(0)) != NULL ) {
        delete item->widget();
        delete item;
    }
}

