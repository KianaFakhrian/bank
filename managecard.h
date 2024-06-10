#ifndef MANAGECARD_H
#define MANAGECARD_H

#include <QDialog>
#include "userfile.h"
#include "cardtocard.h"
#include "see_inventory.h"
#include "change_password.h"
#include "change_permanent_pass.h"
namespace Ui {
class manageCard;
}

class manageCard : public QDialog
{
    Q_OBJECT

public:
    explicit manageCard(QWidget *parent = 0);
    ~manageCard();
    void getUsers(QList<user<unsigned long long>>* userList) ;
    void getUser(user<unsigned long long> User) ;
private slots:
    void on_pushB_Card_to_Card_clicked();

    void on_pushB_inventory_clicked();

    void on_pushB_change_4dgtpass_clicked();

    void on_pushButton_change_permanentPass_clicked();

public slots:
        void OnBackFromCardToCard() ;
        void OnBackFromInventory() ;
        void OnBackFromChange4DgtPass() ;
        void OnBackFromChangePermanentPass() ;

private:
    Ui::manageCard *ui;
    cardTocard* cardtocard ;
    see_inventory* see_Inventory ;
    change_Password* change_password ;
    change_Permanent_pass* change_permanent_pass ;
    QList<user<unsigned long long>>* users ;
    user<unsigned long long> User ;
};

#endif // MANAGECARD_H
