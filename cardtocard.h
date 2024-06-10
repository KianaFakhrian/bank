#ifndef CARDTOCARD_H
#define CARDTOCARD_H

#include <QDialog>
#include "userfile.h"

namespace Ui {
class cardTocard;
}

class cardTocard : public QDialog
{
    Q_OBJECT

public:
    int index_for_account ;

    int index_for_user_to_send_money ;

    explicit cardTocard(QWidget *parent = 0);

    ~cardTocard();

    void getUsers(QList<user<unsigned long long>> *) ;

    bool searchBankAccountForMe(QString cardNum) ;

    bool searchBankAcForOthers(QString cardNum) ;

    void getUser(user<unsigned long long> User) ;

    bool validcvv2() ;

    bool validDate() ;

    void give_time_limitation() ;

    bool enoughMoney = false;

     void writeToTransactionFile_For_receiver(const QString& filePath,QString Data,QString date,QString username) ;

     void writeToTransactionFile_For_me(const QString& filePath,QString Data,QString date,QString username) ;

     void total_Transfer_in_a_day(const QString& filePath,QString date,QString username) ;

     void check_St_password() ;

signals:
     void goback_to_managecard() ;

private slots:

    void updateMyAccount();

    void makeAmountInt() ;

    void updatetheotherAccount() ;

    void on_pushButton_clicked();

    void on_pushB_get_password_clicked();

    void on_lineEdit_stablePass_editingFinished();

    void on_pushButton_back_clicked();

private:
    Ui::cardTocard *ui;

    QList<user<unsigned long long>> * users ;

    user<unsigned long long> User ;

    unsigned long long int amount ;

    QString cardNum1 ;

    QString cardNum2 ;

    bool transfer_acception = false ;

    unsigned long long total_transfer = 0;

    bool password_acception = false ;

    bool rightInfo = false ;
};

#endif // CARDTOCARD_H
