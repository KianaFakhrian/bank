#include "cardtocard.h"
#include "ui_cardtocard.h"
#include "userfile.h"
#include "bankaccount.h"
#include "file_functions.h"
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>

cardTocard::cardTocard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cardTocard)
{
    ui->setupUi(this);
    ui->lineEdit_tmppassword->setReadOnly(true);
    setFixedSize(this->geometry().width(),this->geometry().height());

}

cardTocard::~cardTocard()
{
    delete ui;
}
void cardTocard::getUsers(QList<user<unsigned long long> > *userList)
{
    users = userList ;
}
void cardTocard::getUser(user<unsigned long long> UserInlogin)
{
    User = UserInlogin ;
}


bool cardTocard::searchBankAccountForMe(QString cardNum)
{
    for(int j = 0 ; j < users->size() ; j ++)
    {
        user<unsigned long long>& Users = (*users)[j] ;
        for(int i = 0 ; i < Users.bankAccounts.size() ; i ++)
        {
            if(Users.bankAccounts[i].cardNumber == cardNum )
            {
                index_for_user_to_send_money = j;
                index_for_account = i ;              
            }
        }
    }
    for(int i = 0 ; i < User.bankAccounts.size() ; i ++)
    {
        if(User.bankAccounts[i].cardNumber == cardNum )
        {
            return true ;

        }
    }
    QMessageBox warning ;
    warning.warning(this, "invalid card number","the card number you enterd is not valid for you please try again") ;
    return false ;
}
bool cardTocard::searchBankAcForOthers(QString cardNum)
{
    for(int j = 0 ; j < users->size() ; j ++)
    {
        user<unsigned long long>& Users = (*users)[j] ;
        for(int i = 0 ; i < Users.bankAccounts.size() ; i ++)
        {
            if(Users.bankAccounts[i].cardNumber == cardNum)
            {

                return true ;
            }
        }
    }
    QMessageBox::warning(this, "invalid card number","the card number you enterd does not exist please try again") ;
    return false ;
}
void cardTocard::updateMyAccount()
{

    bool userFound = false ;

    QDateTime currentDate = QDateTime::currentDateTime();
    QString date = currentDate.toString("yyyy-MM-ddHH:mm:ss") ;

    for(int j = 0 ; j < users->size() ; j ++)
    {
        user<unsigned long long>& Users = (*users)[j] ;
        for(int i = 0 ; i < Users.bankAccounts.size() ; i ++)
        {
            if( Users.bankAccounts[i].cardNumber == cardNum1)
            {
                userFound = true ;



                    if(Users.bankAccounts[i].inventory - 5 >= amount)
                    {
                        enoughMoney = true ;
                        Users.bankAccounts[i].inventory -= amount ;
                        break ;
                    }
                    else
                    {
                        enoughMoney = false ;
                        QMessageBox::warning(this,"inventory not sufficient","the inventory is less that the amount ...") ;
                        return;
                    }



            }
        }
        if(userFound)
            break ;
    }
    QString Data = (*users)[index_for_user_to_send_money].bankAccounts[index_for_account].DataSentence() ;
    QString username = (*users)[index_for_user_to_send_money].userName ;
    if(transfer_acception && password_acception)
    {
        file_functions::updateAccountFile("accounts.txt",users->at(index_for_user_to_send_money).bankAccounts.at(index_for_account).cardNumber,*users) ;

        writeToTransactionFile_For_me("transaction.txt", Data,date,username) ;
    }
}
void cardTocard::makeAmountInt()
{
    QString amountStr = ui->lineEdit_amount->text() ;
    amount = amountStr.toULongLong() ;
}

void cardTocard::updatetheotherAccount()
{
    int index_for_account_receiver;
    bool userFound = false ;

    int index_for_user_to_receive_money ;
    for(int j = 0 ; j < users->size() ; j ++)
    {
        user<unsigned long long> &user_to_receive_money = (*users)[j] ;
        for(int i = 0 ;i < user_to_receive_money.bankAccounts.size() ; i ++)
        {

            if( user_to_receive_money.bankAccounts[i].cardNumber == cardNum2 )
            {
                 index_for_user_to_receive_money = j ;
                 index_for_account_receiver = i ;
                 userFound = true ;
                 user_to_receive_money.bankAccounts[i].inventory += amount - amount*0.01 ;
                 break;
            }
        }
        if(userFound)
            break ;
    }
    QDateTime currentDate = QDateTime::currentDateTime();
    QString date = currentDate.toString("yyyy-MM-ddHH:mm:ss") ;

    QString Data = users->at(index_for_user_to_receive_money).bankAccounts.at(index_for_account_receiver).DataSentence() ;
    QString username = (*users)[index_for_user_to_receive_money].userName ;

    file_functions::updateAccountFile("accounts.txt",cardNum2,*users) ;
    writeToTransactionFile_For_receiver("transaction.txt", Data,date,username) ;
}
bool cardTocard::validcvv2()
{
    QString cvv2 =  ui->lineEdit_cvv2->text() ;
    if((*users)[index_for_user_to_send_money].bankAccounts[index_for_account].cvv2 != cvv2)
    {
        QMessageBox::warning(this,"invalid information","enterd cvv2 is not correct") ;
        return false ;
    }
    return true ;
}
bool cardTocard::validDate()
{
    QString date = ui->lineEdit_date->text() ;
    if((*users)[index_for_user_to_send_money].bankAccounts[index_for_account].Date != date)
    {
        QMessageBox::warning(this,"wrong date","entered date is not valid") ;
        return false ;
    }
    return true ;
}
void cardTocard::on_pushButton_clicked()
{
    QDateTime currentDate = QDateTime::currentDateTime();
    QString date = currentDate.toString("yyyy-MM-ddHH:mm:ss") ;


    if(!ui->lineEdit_card_number->text().isEmpty() && !ui->lineEdit->text().isEmpty()
            && !ui->lineEdit_amount->text().isEmpty() &&
            !ui->lineEdit_cvv2->text().isEmpty() && !ui->lineEdit_date->text().isEmpty())
    {

        if(!ui->lineEdit_tmppassword->text().isEmpty() || !ui->lineEdit_stablePass->text().isEmpty())
        {
            cardNum1 = ui->lineEdit_card_number->text();
            if(searchBankAccountForMe(cardNum1))
            {
                bool validCvv2 = validcvv2();
                bool validdate = validDate();
                cardNum2 = ui->lineEdit->text() ;

                if(searchBankAcForOthers(cardNum2) && validCvv2 && validdate)
                {
                    makeAmountInt();
                    if(!ui->lineEdit_stablePass->text().isEmpty())
                    {
                        check_St_password();
                    }
                    else
                    {
                        password_acception = true ;

                    }
                    if(password_acception)
                    {
                        total_Transfer_in_a_day("transaction.txt" ,date,(*users)[index_for_user_to_send_money].userName) ;

                        if(total_transfer <=  100)
                        {
                            transfer_acception = true ;
                            updateMyAccount();

                            if(enoughMoney && transfer_acception && password_acception)
                            {
                                updatetheotherAccount();
                                QMessageBox::information(this,"action completed","card to card has successfully been done") ;
                                ui->lineEdit_tmppassword->clear();
                                ui->lineEdit_stablePass->setReadOnly(false);
                                ui->pushB_get_password->setEnabled(true);
                                ui->lineEdit_stablePass->clear();

                            }
                        }
                        else
                        {
                            QMessageBox::warning(this,"over limit","you have reached to the limit of tranfering money please wait 24 hours and then try again") ;
                            return ;
                        }
                    }
                }
                else
                    return ;
            }
            else
                return ;
        }
        else
        {
            QMessageBox::warning(this,"unfield section","one of the boxes for password has to be filled up") ;
            return ;
        }
    }
    else
    {
        QMessageBox::warning(this,"unfilled sections","please enter the information needed completely") ;
        return ;

    }
}
void cardTocard::on_pushB_get_password_clicked()
{
    QString password ;
    for(int dgt = 0 ; dgt < 4 ; dgt ++)
    {
        int digit = rand() % 10 ;
        password.push_back(QString::number(digit));
    }
    ui->lineEdit_tmppassword->setText(password);
    if(!ui->lineEdit_tmppassword->text().isEmpty())
        ui->lineEdit_stablePass->setReadOnly(true);
}
void cardTocard::writeToTransactionFile_For_receiver(const QString& filePath,QString Data,QString date,QString username)
{
    QFile transaction_file(filePath) ;
    QTextStream out(&transaction_file) ;
    if(!transaction_file.open(QFile::Append | QFile::Text))
    {
        qWarning() << "Failed to open transaction file for writing" ;
    }
    else
        qDebug() << "transaction file successfully opened" ;

    QString transaction_info ;
    transaction_info = "added: " +QString::number(amount - amount*0.01) + " tomans " + date;

    out << username << " " <<Data << " " << transaction_info << "\n";
}
void cardTocard::writeToTransactionFile_For_me(const QString& filePath,QString Data,QString date,QString username)
{
    QFile transaction_file(filePath) ;
    QTextStream out(&transaction_file) ;
    if(!transaction_file.open(QFile::Append | QFile::Text))
    {
        qWarning() << "Failed to open transaction file for writing" ;
    }
    else
        qDebug() << "transaction file successfully opened" ;

    QString transaction_info ;

    transaction_info = "lost: " + QString::number(amount) + " tomans " + date;
    out << username << " " <<Data << " " << transaction_info << "\n";
}
void cardTocard::total_Transfer_in_a_day(const QString& filePath,QString date,QString username)
{

    QFile transaction_file(filePath) ;
    QDateTime now = QDateTime::fromString(date, Qt::ISODate) ;
    QString lost = "lost:" ;
    if(!transaction_file.open(QFile::ReadOnly | QFile::Text))
    {
        qWarning() << "file cannot be opened for reading" ;
    }
    else
        qDebug() << "transaction file opened" ;
    QTextStream in(&transaction_file) ;
    while(!in.atEnd())
    {
        QString line = in.readLine() ;
        QStringList data = line.split(' ') ;
        QDateTime time ;

        if(data.size() == 14 && data[10] == lost && data[0] == username)
        {
            time = QDateTime::fromString(data[13],Qt::ISODate) ;
            if(time.secsTo(now) <= 86400)
            {
                QString strCash = data[11] ;
                total_transfer += strCash.toULongLong() ;
            }
        }
    }
}

void cardTocard::check_St_password()
{
    QString password = ui->lineEdit_stablePass->text() ;
    QString account_password = (*users)[index_for_user_to_send_money].bankAccounts[index_for_account].passWordSt ;

    if(account_password != password)
    {
        QMessageBox::warning(this,"wrong password","the password you enterd was wrong please try again") ;
        return ;
    }
    if(amount > 100)
    {
        QMessageBox::warning(this,"more than limit","unfortunatly you can't transfer more than 100000 tomans with your password. but! you can use active password instead.") ;
        return ;
    }
    password_acception = true ;
    return ;
}
void cardTocard::on_lineEdit_stablePass_editingFinished()
{
    ui->pushB_get_password->setEnabled(false);
}

void cardTocard::on_pushButton_back_clicked()
{
    emit goback_to_managecard();
}
