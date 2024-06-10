#include "makenewaccount.h"
#include "ui_makenewaccount.h"
#include "userfile.h"
#include "file_functions.h"
#include <string>
#include <QString>
#include <QTime>
#include <QDate>
#include <QMessageBox>
makeNewAccount::makeNewAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::makeNewAccount)
{
    ui->setupUi(this);
    setFixedSize(this->geometry().width(),this->geometry().height());


}

makeNewAccount::~makeNewAccount()
{
    delete ui;
}
void makeNewAccount::getUser(user<unsigned long long> *userCpy)
{
    User = userCpy;
}
void makeNewAccount::setUsers(QList<user<unsigned long long> > *userList)
{
    users = userList ;
}
void makeNewAccount::on_radioButton_saving_pressed()
{
    bankAccount<unsigned long long> newAccount ;
    newAccount.type =  "saving"  ;

    make_Shaba(newAccount);
    make_account_num(newAccount);
    make_Card_Num(newAccount);
    make_cvv2(newAccount);
    make_Date(newAccount);
    QMessageBox::StandardButton addOrNot ;
    addOrNot = QMessageBox::question(this,"adding the least amount of inventory" ,"Do you want to add 50 tomans to your inventory ?",QMessageBox::Yes|QMessageBox::No) ;
    if(addOrNot == QMessageBox::Yes)
    {
        newAccount.inventory = 50 ;
    }
    else
        newAccount.inventory = 0 ;
   hide() ;

   make_Password = new make_password(this) ;
   make_Password->setUser(users);
   make_Password->getCard_Number(newAccount.cardNumber);

   connect(make_Password,&make_password::password_updated,this,&makeNewAccount::on_password_updated) ;
   make_Password->show();
   User->bankAccounts.append(newAccount);

   file_functions::writeAccountToFile("accounts.txt",newAccount,User->userName) ;


   emit userUpadted();
}
void makeNewAccount::on_radioButton_current_pressed()
{
    bankAccount<unsigned long long> newAccount ;
    newAccount.type = "current" ;

    make_Shaba(newAccount);
    make_account_num(newAccount);
    make_Card_Num(newAccount);
    make_cvv2(newAccount);
    make_Date(newAccount);

    QMessageBox::StandardButton addOrNot ;
    addOrNot = QMessageBox::question(this,"adding the least amount of inventory" ,"Do you want to add 50 tomans to your inventory ?",QMessageBox::Yes|QMessageBox::No) ;
    if(addOrNot == QMessageBox::Yes)
    {
        newAccount.inventory = 50 ;
    }
    else
        newAccount.inventory = 0 ;
    make_Password = new make_password(this) ;
    make_Password->setUser(users);
    make_Password->getCard_Number(newAccount.cardNumber);

    connect(make_Password,&make_password::password_updated,this,&makeNewAccount::on_password_updated) ;
    make_Password->show();
    User->bankAccounts.append(newAccount);
    file_functions::writeAccountToFile("accounts.txt",newAccount,User->userName) ;
    emit userUpadted();
}

void makeNewAccount::on_radioButton_loan_pressed()
{
    bankAccount<unsigned long long> newAccount ;
    newAccount.type = "loaning" ;
    make_Shaba(newAccount);
    make_account_num(newAccount);
    make_Card_Num(newAccount);
    make_cvv2(newAccount);
    make_Date(newAccount);


    QMessageBox::StandardButton addOrNot ;
    addOrNot = QMessageBox::question(this,"adding the least amount of inventory" ,"Do you want to add 50 tomans to your inventory ?",QMessageBox::Yes|QMessageBox::No) ;
    if(addOrNot == QMessageBox::Yes)
    {
        newAccount.inventory = 50 ;
    }
    else
        newAccount.inventory = 0 ;
    hide() ;
    make_Password = new make_password(this) ;
    make_Password->setUser(users) ;
    make_Password->getCard_Number(newAccount.cardNumber) ;
    connect(make_Password,&make_password::password_updated,this,&makeNewAccount::on_password_updated) ;
    make_Password->show();
    User->bankAccounts.append(newAccount);
    file_functions::writeAccountToFile("accounts.txt",newAccount,User->userName) ;


    emit userUpadted();
}
void makeNewAccount::make_Card_Num(bankAccount<unsigned long long>& newAccount)
{
    for(int i = 0 ; i < 16 ; i ++)
    {
        int num = rand() % 10 ;
        newAccount.cardNumber.push_back(QString::number(num));
    }
}
void makeNewAccount::make_Shaba(bankAccount<unsigned long long>& newAccount )
{
    newAccount.shaba.push_back("IR");

    for(int i = 0 ; i < 3 ; i ++)
    {
        int num = rand() % 10 ;
        newAccount.shaba.push_back(QString::number(num));
    }
    newAccount.shaba.push_back("70001000");
    for(int i = 0 ; i < 13 ; i ++)
    {
        int num = rand() % 10 ;
        newAccount.shaba.push_back(QString::number(num));
    }
}
void makeNewAccount::make_account_num(bankAccount<unsigned long long>& newAccount)
{
    for(int i = 8 ; i < 26 ; i ++)
    {

        newAccount.accountNum.push_back(newAccount.shaba.at(i));
    }
}
void makeNewAccount::make_cvv2(bankAccount<unsigned long long>& newAccount)
{
    for(int i = 0 ; i < 3 ; i++)
    {
        int num = rand() % 10 ;
        newAccount.cvv2.push_back(QString::number(num));
    }
}
void makeNewAccount::make_Date(bankAccount<unsigned long long>& newAccount)
{
    QDate currentDate = QDate::currentDate() ;
    QDate futureDate = currentDate.addYears(3) ;
    newAccount.Date = futureDate.toString("yyyy-MM-dd") ;
}
void makeNewAccount::on_password_updated()
{
    emit password_updated();
    make_Password->close() ;
    show() ;
}
