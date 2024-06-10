#ifndef FILEFUNCIONS_H
#define FILEFUNCIONS_H

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QList>
#include <QDebug>
#include "user.h"
#include "bankaccount.h"
class fileFuncions{
public :
    void readUserFromFile(const QString& filePath , QList<user<unsigned long long>>& users) ;
    void readAccountsFromFile(const QString& filePath , QList<user<unsigned long long>>& users) ;
    void writeUsersToFile(const QString&filePath , QList<user<unsigned long long>>& users) ;
    void writeAccountToFile(const QString&filePath,QList<user<unsigned long long>>&users) ;
};

#endif // FILEFUNCIONS_H#ifndef FILEFUNCTIONS_H

