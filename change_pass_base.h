#ifndef CHANGE_PASS_BASE_H
#define CHANGE_PASS_BASE_H

#include <QDialog>
#include "userfile.h"

namespace Ui {
class change_pass_base;
}

class change_pass_base : public QDialog
{
    Q_OBJECT

public:
    explicit change_pass_base(QWidget *parent = 0);
    virtual ~change_pass_base();

    void getUsers(QList<user<unsigned long long>>* Users) ;

    virtual user<unsigned long long>* searchUser(QString card_number) ;

    virtual bool check_right_new_password(QString firstpass, QString secondpass) ;


private:
    Ui::change_pass_base *ui;
protected:
    QList<user<unsigned long long>>* users ;
    int index_of_account;
    int index_of_user;

};

#endif // CHANGE_PASS_BASE_H
