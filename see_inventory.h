#ifndef SEE_INVENTORY_H
#define SEE_INVENTORY_H

#include <QDialog>
#include "userfile.h"

namespace Ui {
class see_inventory;
}

class see_inventory : public QDialog
{
    Q_OBJECT

public:
    explicit see_inventory(QWidget *parent = 0);
    ~see_inventory();

    void getUsers(QList<user<unsigned long long>> users) ;
signals:
    void goTo_ManageCardPage() ;

private slots:
    void on_pushButton_show_inventory_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::see_inventory *ui;
    QList<user<unsigned long long>> users ;
};

#endif // SEE_INVENTORY_H
