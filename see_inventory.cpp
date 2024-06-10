#include "see_inventory.h"
#include "ui_see_inventory.h"
#include <QMessageBox>
see_inventory::see_inventory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::see_inventory)
{
    ui->setupUi(this);
    setFixedSize(this->geometry().width(),this->geometry().height());

}

see_inventory::~see_inventory()
{
    delete ui;
}

void see_inventory::on_pushButton_show_inventory_clicked()
{
    QString card_number = ui->lineEdit_card_number->text() ;
    QString password = ui->lineEdit_password->text() ;
    bool cardFound = false ;
    for(int i = 0 ; i < users.size() ; i++)
    {
        user<unsigned long long> User = users[i] ;
        for(int j = 0 ; j < User.bankAccounts.size() ; j ++)
        {
            if(User.bankAccounts[j].cardNumber == card_number)
            {
                cardFound = true ;
                if(User.bankAccounts[j].passWordSt == password)
                {
                    ui->label_inventory->setText(QString::number(User.bankAccounts[j].inventory)) ;
                }
                else
                    QMessageBox::warning(this,"invalid password","the password is wrong please try again") ;

            }


        }
    }
    if(!cardFound)
    {
        QMessageBox::warning(this,"invalid card number","the card number you enterd is wrong please try another one") ;
        return ;
    }
}
void see_inventory::getUsers(QList<user<unsigned long long>> Users)
{
    users = Users ;
}

void see_inventory::on_pushButton_back_clicked()
{
    emit goTo_ManageCardPage();
}
