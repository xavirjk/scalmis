#include "accounts.h"
namespace SCALMIS {
namespace models {
Accounts::Accounts(QObject *parent) : Entity(parent,"Accounts")
{
    fullname = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"fullName","fullName")));
    pjno = static_cast<IntDecorator*>(addItem(new IntDecorator(this,"pjno","PJ-Number")));
    email = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"email","Email Address")));
    office = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"office","Office")));
    password = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"password","Password")));
    authType = static_cast<IntDecorator*>(new IntDecorator(this,"authType","Auth Type"));
    typeModel = {
        {"Admin",1},
        {"User",0}
    };
    typeComboSelect = static_cast<ComboSelect*>(new ComboSelect(this,typeModel));
}
Accounts::Accounts(QObject *parent, const QJsonObject &json):
    Accounts(parent){
    update(json);
}
Accounts::~Accounts(){}
}}
