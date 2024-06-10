#include "change_pass_base.h"
#include "ui_change_pass_base.h"

change_pass_base::change_pass_base(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_pass_base)
{
    ui->setupUi(this);
    setFixedHeight(800);
    setFixedWidth(600);
}

change_pass_base::~change_pass_base()
{
    delete ui;
}
void change_pass_base::getUsers(QList<user<unsigned long long> > *Users)
{
    users = Users ;
}
user<unsigned long long>* change_pass_base::searchUser(QString card_number)
{
    for(int i = 0 ; i < users->size() ; i ++)
    {
        user<unsigned long long>& User = (*users)[i] ;
        for(int j = 0 ; j < User.bankAccounts.size() ; j ++)
        {
              if(User.bankAccounts[j].cardNumber == card_number)
              {
                  index_of_user = i ;
                  index_of_account = j ;
                  return &User ;
              }
        }
    }
    return nullptr ;

}
bool change_pass_base::check_right_new_password(QString firstpass, QString secondpass)
{
    if(firstpass == secondpass)
        return true ;
    else
        return false ;

}
