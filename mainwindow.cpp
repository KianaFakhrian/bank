#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cardtocard.h"

#include <QMessageBox>
#include <QList>
#include "userfile.h"
#include "dialogsec.h"
#include "signinpage.h"
#include "file_functions.h"


using namespace std ;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readUsers();
    readAccounts();
    setFixedSize(this->geometry().width(),this->geometry().height());

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    QString userName = ui->lineEdit_userName->text();
    QString passWord = ui->lineEdit_passWord->text();

    if(validUserPass(userName,passWord))
    {
        goToMainPage();
        dialogSec->getUsername(userName) ;
        dialogSec->setUsers(&users) ;
    }
    else
        QMessageBox::warning(this,"login failed","userName or password is worng") ;
}
void MainWindow::readUsers()
{
    file_functions::readUsersFromFile("users.txt",users);
}
void MainWindow::readAccounts()
{
    file_functions::readAccountsFromFile("accounts.txt",users);
}
bool MainWindow::validUserPass(const QString &userName,const QString &passWord)
{
    readUsers();

    for(const user<unsigned long long> &User : users)
    {
        if(User.userName == userName && User.password == passWord)
            return true ;
    }
    return false ;
}
void MainWindow::goToMainPage()
{
    hide() ;
    dialogSec->setUsers(&users);
    dialogSec = new DialogSec(this) ;
    dialogSec->show();
}
void MainWindow::goToSignInPage()
{
    hide() ;
    signInPage = new signinPage(this) ;
    signInPage->setUsers(&users);
    connect(signInPage,&signinPage::userAdded,this,&MainWindow::updateUserList) ;
    signInPage->show() ;

}
void MainWindow::on_pushButton_2_clicked()
{
    goToSignInPage();
}
void MainWindow::updateUserList(user<unsigned long long> User)
{
    users.append(User);
    signInPage->close() ;
    this->show() ;
}
