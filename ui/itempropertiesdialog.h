#ifndef ITEMPROPERTIESDIALOG_H
#define ITEMPROPERTIESDIALOG_H

#include <QDialog>

namespace Ui {
    class ItemPropertiesDialog;
}

class ItemPropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ItemPropertiesDialog(QWidget *parent = 0);
    ~ItemPropertiesDialog();

public :
    bool isCancelled() const { return isCancel; }

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::ItemPropertiesDialog *ui;

private:
    bool isCancel;
};

#endif // ITEMPROPERTIESDIALOG_H
