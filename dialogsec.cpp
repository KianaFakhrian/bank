#include "dialogsec.h"
#include "ui_dialogsec.h"
#include "userfile.h"
#include "makenewaccount.h"

#include <QMessageBox>

DialogSec::DialogSec(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSec)
{
    ui->setupUi(this);
    setFixedSize(this->geometry().width(),this->geometry().height());


}

DialogSec::~DialogSec()
{
    delete ui;
}
void DialogSec::getUsername(const QString& userName)
{
    username = userName;
}

void DialogSec::on_pushBMakeNew_clicked()
{
    for(user<unsigned long long>& User : *users)
    {

        if(User.userName == username)
        {
            hide() ;
            if(User.bankAccounts.size() < 5)
            {

                makenewaccount = new makeNewAccount(this) ;
                makenewaccount->setUsers(users) ;
                makenewaccount->getUser(&User) ;
                connect(makenewaccount,&makeNewAccount::userUpadted,this,&DialogSec::onUserUpdated) ;
                makenewaccount->show() ;
            }
            else
            {
                QMessageBox error ;
                error.warning(this,"account number limit","the number of your accounts is top to the limit") ;
            }
            break ;
        }
    }
}
void DialogSec::setUsers(QList<user<unsigned long long>>* userList)
{
    users = userList ;
}
void DialogSec::onUserUpdated()
{
    emit userUpdated();
    makenewaccount->close() ;
    show() ;
}
void DialogSec::on_pushBGoTo_clicked()
{
    hide() ;
    managecard = new manageCard(this) ;
    managecard->getUsers(users);
    for(user<unsigned long long> User : *users)
    {
        if(User.userName == username)
        {
            managecard->getUser(User);
            break ;
        }
    }
    managecard->show();
}
