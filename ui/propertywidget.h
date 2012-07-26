#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include <QWidget>

#include "model/order.h"

class QGroupBox;
class QHBoxLayout;
class QSignalMapper;
class QGridLayout;
class QToolButton;
class QVBoxLayout;

class PropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertyWidget(QWidget *parent = 0);
    
signals:

public slots:
    void setOrder(Model::Order order);
    void setCurrentComponent(int);

private:
    enum {
        NumButtons = 8 , ButtonsPerLine = 8
    };

    QSignalMapper *signalMapper;

    QGroupBox *orderGroupBox;
    QGroupBox *componentsGroupBox;
    QGroupBox *additionalsGroupBox;

    QGridLayout *orderGridLayout;
    QGridLayout *componentsGridLayout;
    QGridLayout *additionalsGridLayout;

    void initOrder();
    void initComponents();
    void initAdditionals();
};

#endif // PROPERTYWIDGET_H
