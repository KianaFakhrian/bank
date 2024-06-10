#ifndef FILEFUNCIONS_H
#define FILEFUNCIONS_H

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QList>
#include <QString>
#include <QDebug>
#include <QTemporaryFile>
#include "userfile.h"
#include "bankaccount.h"
class file_functions{
public:
    static void readUsersFromFile(const QString& filePath ,QList<user<unsigned long long>>& users)
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

    static void readAccountsFromFile(const QString& filepath , QList<user<unsigned long long>>& users)
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
            if(data.size() >= 10)
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

    static void writeUserToFile(const QString&filePath , user<unsigned long long> users)
    {
        QFile file(filePath);

        if (!file.open(QFile::Append | QFile::Text)) {
            qWarning() << "Cannot open file for writing:" << file.errorString();
            return;
        }
        QTextStream out(&file) ;

            out << users.name << " " << users.lastName << " "
                << users.userName << " "
                << users.ID << " " << users.password<<" "<< users.age << "\n" ;

        file.close();
    }

    static void writeAccountToFile(const QString &filePath, bankAccount<unsigned long long> account,QString username)
    {
        QFile file(filePath) ;
        if(!file.open(QFile::Append | QFile::Text))
        {
            qWarning() << "Couldn't open file" <<file.errorString() ;
            return ;
        }
        QTextStream out(&file) ;


            out << username << " " << account.DataSentence() <<"\n" ;

    }
    static void updateAccountFile(const QString& filePath,QString cardNumber,QList<user<unsigned long long>> users)
    {
        QString updated_line ;
        bool userFound = false ;
        for(user<unsigned long long> User : users)
        {
            for(bankAccount<unsigned long long> BankAccount : User.bankAccounts)
            {
                if(BankAccount.cardNumber == cardNumber)
                {
                    updated_line = User.userName + " " + BankAccount.DataSentence();
                    userFound = true ;
                    break ;
                }
            }
            if(userFound)
                break ;
        }

            QFile originalFile(filePath);
            if (!originalFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qWarning() << "Failed to open original file for reading:" << originalFile.errorString();
                return;
            }


            QString tempFilePath = filePath + ".tmp";
            QFile tempFile(tempFilePath);
            if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                qWarning() << "Failed to create temporary file:" << tempFile.errorString();
                originalFile.close();
                return;
            }

            QTextStream out(&tempFile);

            QTextStream in(&originalFile);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList data = line.split(' ');

                if (data.size() > 1 && data[2] == cardNumber) {
                    out << updated_line << '\n';
                } else {
                    out << line << '\n';
                }
            }

            originalFile.close();
            tempFile.close();

            if (!QFile::remove(filePath)) {
                qWarning() << "Failed to remove original file:" << filePath;
            } else {
                if (!QFile::rename(tempFilePath, filePath)) {
                    qWarning() << "Failed to rename temporary file to original file:" << tempFilePath;
                } else {
                    qDebug() << "File updated successfully.";
                }
            }
        }
};
#endif // FILEFUNCIONS_H#ifndef FILEFUNCTIONS_H

