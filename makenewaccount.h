#ifndef MAKENEWACCOUNT_H
#define MAKENEWACCOUNT_H

#include <QDialog>
#include "userfile.h"
#include "make_password.h"

namespace Ui {
class makeNewAccount;
}

class makeNewAccount : public QDialog
{
    Q_OBJECT

public:
    explicit makeNewAccount(QWidget *parent = 0);
    ~makeNewAccount();

    void setUsers(QList<user<unsigned long long>>* userList) ;

    void getUser(user<unsigned long long>* userCpy) ;

    void make_Card_Num(bankAccount<unsigned long long> &newAccount) ;

    void make_Shaba(bankAccount<unsigned long long> &newAccount)  ;

    void make_account_num(bankAccount<unsigned long long>& newAccount) ;

    void make_cvv2(bankAccount<unsigned long long>& newAccount) ;

    void make_Date(bankAccount<unsigned long long>& newAccount) ;

    int cnt = 0;

signals:
    void userUpadted() ;
    void password_updated() ;

private slots:

    void on_radioButton_saving_pressed();

    void on_radioButton_current_pressed();

    void on_radioButton_loan_pressed();

    void on_password_updated() ;
private:
    Ui::makeNewAccount *ui;

    make_password* make_Password ;

    QList<user<unsigned long long>>* users ;

    user<unsigned long long> *User ;
};

#endif // MAKENEWACCOUNT_H
