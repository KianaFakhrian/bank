#ifndef USER_H
#define USER_H
#include "bankaccount.h"
#include <QString>
#include <QList>
template <class T>
class user
{
public:
    QString name, lastName, userName ;
    QString ID ;
    QString password ;
    QList<bankAccount<unsigned long long>> bankAccounts ;
    user* head ;
    user* tail ;

public:
    user()
    {
        head = nullptr ;
        tail = nullptr ;
    }
    void pushBack(bankAccount<T> newAccount)
    {
        bankAccount<T>* tmp = new  bankAccount<T>;
        tmp->setCardNumber(newAccount.getCardNum());
        tmp->setShaba(newAccount.getShaba());
        tmp->setType(newAccount.getType());
        if(head == nullptr)
        {
            head = tmp ;
            tail = head ;
            tmp->n = nullptr ;
            tmp->pre = nullptr ;
            return ;
        }
        tmp->pre = tail ;
        tail = tmp ;
        tmp->n = nullptr ;
    }
    void loadData(const QStringList& data)
    {
        if(data.size() >= 5)
        {
            name = data.at(0) ;
            lastName = data.at(1) ;
            userName = data.at(2) ;
            ID = data.at(3) ;
            password = data.at(4) ;
        }
    }
};

#endif // USER_H
