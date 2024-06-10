#include "signinpage.h"
#include "ui_signinpage.h"
#include "file_functions.h"
#include <QMessageBox>

signinPage::signinPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signinPage)
{
    ui->setupUi(this);
    setFixedSize(this->geometry().width(),this->geometry().height());


}

signinPage::~signinPage()
{
    delete ui;
}
void signinPage::setUsers(QList<user<unsigned long long>>* userList)
{
    users = userList ;
}

void signinPage::on_pushButton_clicked()
{
    user<unsigned long long> new_User ;
    if(ui->lineEdit_age->text().isEmpty() || ui->lineEdit_ID->text().isEmpty()
            || ui->lineEdit_lastName->text().isEmpty() || ui->lineEdit_name->text().isEmpty()
            || ui->lineEdit_pass->text().isEmpty() || ui->lineEdit_username->text().isEmpty())
    {
        QMessageBox::warning(this,"unfilled field","please fill all fields") ;
        return ;
    }
    if(right_Username)
    {
        new_User.userName = ui->lineEdit_username->text() ;
        new_User.password = ui->lineEdit_pass->text() ;
        new_User.name = ui->lineEdit_name->text() ;
        new_User.lastName = ui->lineEdit_lastName->text() ;
        new_User.age = ui->lineEdit_age->text() ;
        new_User.ID = ui->lineEdit_ID->text() ;

        users->append(new_User);
        file_functions::writeUserToFile("users.txt" ,new_User) ;
        emit userAdded(new_User);
        return ;
    }
    else
    {
        QMessageBox::warning(this,"incorrect information","please fill the fields correctly") ;
        return ;
    }


}

void signinPage::on_lineEdit_username_editingFinished()
{
    for(const user<unsigned long long>& Users : *users )
    {
        if( ui->lineEdit_username->text() == Users.userName)
        {
            QMessageBox::warning(this,"invalid username","the username already exists please choose another one") ;
            right_Username = false ;
            return ;
        }

    }
    right_Username = true ;
}
