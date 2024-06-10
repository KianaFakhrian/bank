#ifndef MAKE_PASSWORD_H
#define MAKE_PASSWORD_H

#include <QDialog>
#include "userfile.h"


namespace Ui {
class make_password;
}

class make_password : public QDialog
{
    Q_OBJECT

public:
    explicit make_password(QWidget *parent = 0);
    ~make_password();

    void setUser(QList<user<unsigned long long>> *UsersList ) ;

    void getCard_Number(QString card_number) ;


signals:
    void password_updated() ;
private slots:
    void on_pushButton_save_clicked();

private:
    Ui::make_password *ui;
    QList<user<unsigned long long>> *users ;
    QString card_number ;
};

#endif // MAKE_PASSWORD_H
