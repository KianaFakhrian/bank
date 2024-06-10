#ifndef DIALOGSEC_H
#define DIALOGSEC_H

#include <QDialog>
#include "userfile.h"
#include "makenewaccount.h"
#include "managecard.h"
#include "cardtocard.h"

namespace Ui {
class DialogSec;
}

class DialogSec : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSec(QWidget *parent = 0);
    ~DialogSec();
    void getUsername(const QString& username) ;
    void setUsers(QList<user<unsigned long long>>* userList) ;
signals:
    userUpdated() ;
private slots:

    void on_pushBMakeNew_clicked();

    void onUserUpdated() ;

//    void on_pushBGoTo_clicked();

    void on_pushBGoTo_clicked();

private:
    Ui::DialogSec *ui;
    makeNewAccount* makenewaccount ;
    manageCard* managecard ;

    QString username ;
    QList<user<unsigned long long>>* users ;

};

#endif // DIALOGSEC_H
