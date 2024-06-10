#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QList>
#include "dialogsec.h"
#include "signinpage.h"
#include "userfile.h"

using namespace std ;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
public slots:
    void updateUserList(user<unsigned long long> User) ;

private:
    Ui::MainWindow *ui;
    DialogSec* dialogSec ;
    signinPage* signInPage ;
    QList<user<unsigned long long>> users ;

    void readUsers() ;
    void readAccounts() ;
    bool validUserPass(const QString &userName,const QString &password) ;
    void goToMainPage() ;
    void goToSignInPage() ;
};
#endif // MAINWINDOW_H
