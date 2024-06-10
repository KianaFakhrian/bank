#include "filefuncions.h"

void fileFuncions::readUserFromFile(const QString& filePath,QList<user<unsigned long long>> users)
{
    QFile file(filePath) ;
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qWarning() << "file couldn't be open" << file.errorString() ;
        return ;
    }
    QTextStream in(&file) ;
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList data = line.split(' ');

        user<unsigned long long> tmpUser ;
        tmpUser.loadData(data) ;
        users.append(tmpUser);
    }
    file.close();
}
void fileFuncions::readAccountsFromFile(const QString& filepath,QList<user<unsigned long long>>& users)
{
    QFile file(filepath) ;

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qWarning() << "file couldn't be open" << file.errorString() ;
        return ;
    }
    QTextStream in(&file) ;
    while(!in.atEnd())
    {
        QString line = in.readLine() ;
        QStringList data = line.split(' ') ;
        bankAccount<unsigned long long> account ;
        if(data.size() >= 11)
        {
            QString userName = data.at(0) ;
            bankAccount<unsigned long long> account ;
            account.loadData(data.mid(1));

            for(user<unsigned long long>& User : users)
            {
                if(User.userName == userName)
                    User.bankAccounts.append(account);
            }
        }
    }
    file.close();
}
void fileFuncions::writeUsersToFile(const QString& filePath,const QList<user<unsigned long long>>& users)
{
    QFile file(filePath);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qWarning() << "Cannot open file for writing:" << file.errorString();
        return;
    }
    QTextStream out(&file) ;
    for(const user<unsigned long long>& User : users)
    {
        out << User.name << " " << User.lastName << " "
            << User.userName << " "
            << User.ID << " " << User.password << "\n" ;
    }
    file.close();
}
void fileFuncions::writeAccountToFile(const QString& filePath , const QList<user<unsigned long long>> &users)
{
    QFile file(filePath) ;
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        qWarning() << "Coudl'nt open file" <<file.errorString() ;
        return ;
    }
    QTextStream out(&file) ;
    for(const user<unsigned long long>& User : users)
    {
        for(const bankAccount<unsigned long long>& account : User.bankAccounts)
        {
            out << User.userName << " " << account.DataSentence() <<"\n" ;
        }
    }
}
//----------------------------------------------------------
