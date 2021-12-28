#include "authlogin.h"

namespace SCALMIS {
namespace models {
AuthLogin::AuthLogin(QObject *parent) : Entity(parent,"authLogin")
{
    pjno = static_cast<IntDecorator*>(addItem(new IntDecorator(this,"pjno","PJ-Number")));
    password = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"password","Password")));
}
AuthLogin::AuthLogin(QObject *parent, const QJsonObject &json):AuthLogin(parent)
{
    update(json);
}

AuthLogin::~AuthLogin(){}

}}

