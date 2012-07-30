#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QSignalMapper>

#include "categorieswidget.h"
#include "itemswidget.h"
#include "sizewidget.h"
#include "propertywidget.h"
#include "itempropertiesdialog.h"

class HeaderWidget;
class OrderWidget;
class SlidingStackedWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum WidgetPage {
        CategoryPage = 0,
        ItemPage = 1,
        SizePage = 2,
        PropertyPage = 3
    };

    explicit MainWindow(int aUserId, QWidget *parent = 0);
    ~MainWindow();

signals:
    void orderAdded(QList<Model::OrderDetail> orders);

private slots:
    void ShowHomePage();
    void reportClickedSlot();
    void orderItemClicked(QString orderIndexId);
    void systemClickedSlot();
    void logoutClickedSlot();
    void applyOrderClickedSlot();
    void cancelOrderClickedSlot();
    void selectCategorySlot(int categoryId);
    void selectItemSlot(int itemId);
    void selectItemDetialSlot(int itemDetialId);
    void updateItemDetialSlot(Model::OrderDetail order);

private:
    QSignalMapper *signalMapper;
    HeaderWidget *headerWidget;
    OrderWidget* orderWidget;
    SlidingStackedWidget *stackedWidget;

    CategoriesWidget* categoriesWidget;
    ItemsWidget* itemsWidget;
    SizeWidget* sizeWidget;
    PropertyWidget* propertyWidget;

    QLabel *versionLabel;
    QLabel *helpLabel;

    QList<Model::OrderDetail> orders;
    int discount ;
    int userId;
    Model::OrderDetail getOrderByIndexId(QString indexId);

    void setWindowSize();
    void createWidgetPages();
    void createDockWidgets();
    void createStatusBar();
    void establishConnections();
    void createHeaderDockWidget();
    void createOrderDockWidget();
    void setCurrentPage(WidgetPage page);
    void addLoginEvent();
    void AddLogoutEvent();
    void updateOrder(Model::OrderDetail oldOrder, Model::OrderDetail newOrder);
    void computeTotalCash();
    void computeFree();
    void computeCupon();
    void setDiscount();
    void clearShoppingCart();
};

#endif // MAINWINDOW_H
