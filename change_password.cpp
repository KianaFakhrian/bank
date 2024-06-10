#include "change_password.h"
#include "ui_change_password.h"
#include "file_functions.h"
#include <QMessageBox>
#include <QDebug>

change_Password::change_Password(QWidget *parent) :
    change_pass_base(parent),
    ui(new Ui::change_Password)
{
    ui->setupUi(this);
    setFixedHeight(800);
    setFixedWidth(600);
}

change_Password::~change_Password()
{
    delete ui;
}

void change_Password::on_pushButton_clicked()
{
    if(!ui->lineEdit_recent_pass->text().isEmpty()
            && !ui->lineEdit_new_pass->text().isEmpty() && !ui->lineEdit_verify_new_pass->text().isEmpty() && !ui->lineEdit_cardnumber->text().isEmpty())
    {
        QString card_number = ui->lineEdit_cardnumber->text() ;
        QString recent_pass = ui->lineEdit_recent_pass->text() ;
        QString new_pass = ui->lineEdit_new_pass->text() ;
        QString verify_new_pass = ui->lineEdit_verify_new_pass->text() ;
        user<unsigned long long>* User = searchUser(card_number) ;
        if(User != nullptr && right_recent_pass(recent_pass))
        {
            if(check_right_new_password(new_pass,verify_new_pass))
            {
                User->bankAccounts[index_of_account].pass4Dgt = new_pass ;
                file_functions::updateAccountFile("accounts.txt",User->bankAccounts[index_of_account].cardNumber ,*users) ;
                QMessageBox::information(this,"action completed","your four digit password changed successfully") ;
                emit goback_to_manageCard();
            }
        }
        else
        {
            QMessageBox::warning(this, "Invalid password","the recent password is wrong please try again") ;
            return ;
        }

    }
    else
        QMessageBox::warning(this,"Incomplete information","please fill in all fields") ;
}
bool change_Password::right_recent_pass(QString password)
{
    if((*users)[index_of_user].bankAccounts[index_of_account].pass4Dgt == password)
    {
        return true ;
    }
    return false ;
}
