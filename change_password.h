#ifndef CHANGE_PASSWORD_H
#define CHANGE_PASSWORD_H

#include <QDialog>
#include "userfile.h"
#include "change_pass_base.h"

namespace Ui {
class change_Password;

}
class change_Password : public change_pass_base
{
    Q_OBJECT

public:
    explicit change_Password(QWidget *parent = 0);
    ~change_Password();

    bool right_recent_pass(QString password) ;


signals:
    void goback_to_manageCard() ;

private slots:
    void on_pushButton_clicked();

private:
    Ui::change_Password *ui;
};

#endif // CHANGE_PASSWORD_H
