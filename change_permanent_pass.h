#ifndef CHANGE_PERMANENT_PASS_H
#define CHANGE_PERMANENT_PASS_H

#include <QDialog>
#include "userfile.h"
#include "change_pass_base.h"

namespace Ui {
class change_Permanent_pass;
}

class change_Permanent_pass : public change_pass_base
{
    Q_OBJECT

public:
    explicit change_Permanent_pass(QWidget *parent = 0);
    ~change_Permanent_pass();
    bool right_recent_pass(QString) ;

signals:
    void goback_to_manageCardsPanel() ;
private slots:
    void on_pushButton_save_clicked();


private:
    Ui::change_Permanent_pass *ui;

};

#endif // CHANGE_PERMANENT_PASS_H
