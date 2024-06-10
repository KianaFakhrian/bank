#include "make_password.h"
#include "ui_make_password.h"
#include "file_functions.h"
#include <QMessageBox>
#include <QString>

make_password::make_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::make_password)
{
    ui->setupUi(this);
}

make_password::~make_password()
{
    delete ui;
}
void make_password::setUser(QList<user<unsigned long long> > *UsersList)
{
    users = UsersList ;
}

void make_password::on_pushButton_save_clicked()
{
    if(ui->lineEdit_4dgt->text().isEmpty() || ui->lineEdit_permanent_pass->text().isEmpty())
    {
        QMessageBox::warning(this,"unfilled box","please fill all the boxes") ;
        return ;
    }
    QString fourDgtPass = ui->lineEdit_4dgt->text() ;

    QString permanent_pass = ui->lineEdit_permanent_pass->text() ;

    for(int i = 0 ; i < users->size() ; i ++)
    {
        user<unsigned long long>& Usertmp = (*users)[i] ;
        for(int j = 0 ; j < Usertmp.bankAccounts.size() ; j++)
        {
            if(Usertmp.bankAccounts[j].cardNumber == card_number)
            {
                Usertmp.bankAccounts[j].pass4Dgt = fourDgtPass ;
                Usertmp.bankAccounts[j].passWordSt = permanent_pass ;
            }
        }
    }
    file_functions::updateAccountFile("accounts.txt",card_number,*users) ;
    hide() ;
}
void make_password::getCard_Number(QString card_number)
{
    this->card_number = card_number ;
}

