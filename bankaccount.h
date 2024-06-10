#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <QString>

template <class T>
class bankAccount
{
public:
    QString type ;
    QString cardNumber , shaba ,accountNum , cvv2 ;
    T inventory;
    QString Date ;
    QString pass4Dgt , passWordSt , activePass ;
    bankAccount* pre ;
    bankAccount* n ;
    void loadData(const QStringList& data)
    {
        if(data.size() >= 9)
        {
            type = data.at(0);
            cardNumber = data.at(1) ;
            shaba = data.at(2) ;
            accountNum = data.at(3) ;
            cvv2 = data.at(4) ;
            inventory = data.at(5).toDouble() ;
            Date = data.at(6) ;
            pass4Dgt = data.at(7) ;
            passWordSt = data.at(8) ;
        }
    }

    QString DataSentence() const
    {
        return type+" " + cardNumber
                + " " + shaba + " " + accountNum + " " +
                cvv2 + " " + QString::number(inventory) + " " + Date + " " +
                pass4Dgt + " " + passWordSt ;
    }
};
#endif // BANKACCOUNT_H
