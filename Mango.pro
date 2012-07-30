#-------------------------------------------------
#
# Project created by QtCreator 2012-07-13T14:23:46
#
#-------------------------------------------------

QT       += core gui sql declarative

TARGET = Mango
TEMPLATE = app

SOURCES += main.cpp\
    model/category.cpp \
    model/component.cpp \
    model/item.cpp \
    database/databasemanager.cpp \
    ui/categorieswidget.cpp \
    ui/mainwindow.cpp \
    ui/sizewidget.cpp \
    ui/itemswidget.cpp \
    model/itemdetail.cpp \
    ui/headerwidget.cpp \
    ui/orderwidget.cpp \
    ui/itempropertiesdialog.cpp \
    model/additionals.cpp \
    ui/SlidingStackedWidget.cpp \
    model/orderobject.cpp \
    ui/propertywidget.cpp \
    model/orderdetail.cpp \
    model/order.cpp \
    model/login.cpp \
    model/user.cpp

HEADERS  += model/category.h \
    model/component.h \
    model/item.h \
    database/databasemanager.h \
    ui/categorieswidget.h \
    ui/mainwindow.h \
    ui/sizewidget.h \
    model/itemdetail.h \
    ui/itemswidget.h \
    ui/headerwidget.h \
    ui/orderwidget.h \
    model/itemdetail.h \
    ui/itempropertiesdialog.h \
    model/additionals.h \
    ui/SlidingStackedWidget.h \
    model/orderobject.h \
    ui/propertywidget.h \
    model/orderdetail.h \
    model/login.h \
    model/order.h \
    model/user.h \
    model/constants.h

FORMS += \
    ui/itempropertiesdialog.ui


RESOURCES += \
    resources.qrc

OTHER_FILES += \
    mango.qss \
    ui/qml/orderlist.qml





























