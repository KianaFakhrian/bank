#include "managecard.h"
#include "ui_managecard.h"
#include "userfile.h"

manageCard::manageCard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manageCard)
{
    ui->setupUi(this);
    setFixedSize(this->geometry().width(),this->geometry().height());

}

manageCard::~manageCard()
{
    delete ui;
}

void manageCard::on_pushB_Card_to_Card_clicked()
{
    hide() ;
    cardtocard = new cardTocard(this) ;
    cardtocard->getUser(User);
    cardtocard->getUsers(users);
    connect(cardtocard , &cardTocard::goback_to_managecard,this,&manageCard::OnBackFromCardToCard);

    cardtocard->show();
}
void manageCard::getUsers(QList<user<unsigned long long>>* userList)
{
    users = userList ;
}
void manageCard::getUser(user<unsigned long long> UserInLogin)
{
    User = UserInLogin ;
}
void manageCard::OnBackFromCardToCard()
{
    cardtocard->close() ;
    this->show();
}

void manageCard::OnBackFromInventory()
{
    see_Inventory->close() ;
    this->show();
}
void manageCard::OnBackFromChange4DgtPass()
{
    change_password->close() ;
    this->show();
}
void manageCard::OnBackFromChangePermanentPass()
{
    change_permanent_pass->close() ;
    this->show() ;
}

void manageCard::on_pushB_inventory_clicked()
{
    hide() ;
    see_Inventory = new see_inventory(this) ;
    see_Inventory->getUsers(*users);
    connect(see_Inventory,&see_inventory::goTo_ManageCardPage,this,&manageCard::OnBackFromInventory) ;

    see_Inventory->show();
}

void manageCard::on_pushB_change_4dgtpass_clicked()
{
    hide() ;
    change_password = new change_Password(this) ;
    change_password->getUsers(users);
    connect(change_password,&change_Password::goback_to_manageCard,this,&manageCard::OnBackFromChange4DgtPass) ;
    change_password->show();
}
void manageCard::on_pushButton_change_permanentPass_clicked()
{
    hide() ;
    change_permanent_pass = new change_Permanent_pass(this) ;
    change_permanent_pass->getUsers(users);
    connect(change_permanent_pass,&change_Permanent_pass::goback_to_manageCardsPanel,this,&manageCard::OnBackFromChangePermanentPass) ;
    change_permanent_pass->show();
}
