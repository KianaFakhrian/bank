#ifndef SIGNINPAGE_H
#define SIGNINPAGE_H

#include <QDialog>
#include <QString>
#include "userfile.h"

namespace Ui {
class signinPage;
}

class signinPage : public QDialog
{
    Q_OBJECT

public:
    explicit signinPage(QWidget *parent = 0);
    ~signinPage();
    void setUsers(QList<user<unsigned long long>>* userList) ;
    void goToLoginPage() ;

signals:
//    void signInCompleted(QList<user<unsigned long long>>&userList) ;
    void userAdded(user<unsigned long long> User) ;
private slots:

    void on_pushButton_clicked();


    void on_lineEdit_username_editingFinished();

private:
    Ui::signinPage *ui;
    QList<user<unsigned long long>>* users ;
    bool right_Username ;
};

#endif // SIGNINPAGE_H
