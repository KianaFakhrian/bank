#include "change_permanent_pass.h"
#include "ui_change_permanent_pass.h"
#include <QMessageBox>
#include "file_functions.h"
change_Permanent_pass::change_Permanent_pass(QWidget *parent) :
    change_pass_base(parent),
    ui(new Ui::change_Permanent_pass)
{
    ui->setupUi(this);
    setFixedSize(this->geometry().width(),this->geometry().height());

}

change_Permanent_pass::~change_Permanent_pass()
{
    delete ui;
}
void change_Permanent_pass::on_pushButton_save_clicked()
{
    if(!ui->lineEdit_recent_pass->text().isEmpty()
            && !ui->lineEdit_new_pass->text().isEmpty() && !ui->lineEdit_verify_new_pass->text().isEmpty() && !ui->lineEdit_cardnumber->text().isEmpty() )
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
                User->bankAccounts[index_of_account].passWordSt = new_pass ;
                file_functions::updateAccountFile("accounts.txt",User->bankAccounts[index_of_account].cardNumber ,*users) ;
                QMessageBox::information(this,"action completed","your four digit password changed successfully") ;
                emit goback_to_manageCardsPanel();
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
bool change_Permanent_pass::right_recent_pass(QString password)
{
    qDebug() << index_of_account << " " << index_of_user << "\n";
    if((*users)[index_of_user].bankAccounts[index_of_account].passWordSt == password)
    {
        return true ;
    }
    return false ;

}
