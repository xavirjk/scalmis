#ifndef AUTHLOGIN_H
#define AUTHLOGIN_H

#include <QObject>
#include <QJsonObject>
#include <SCALMIS-LIB_global.h>
#include <data/stringdecorator.h>
#include <data/intdecorator.h>
#include <data/entity.h>
using namespace SCALMIS::data;
namespace SCALMIS {
namespace models {
class SCALMISLIB_EXPORT AuthLogin : public Entity
{
    Q_OBJECT

    Q_PROPERTY(SCALMIS::data::IntDecorator *ui_pjno MEMBER pjno CONSTANT)
    Q_PROPERTY(SCALMIS::data::StringDecorator *ui_password MEMBER password CONSTANT)
public:
    explicit AuthLogin(QObject *parent = nullptr);
    AuthLogin(QObject *parent, const QJsonObject &json);
    ~AuthLogin();

    IntDecorator *pjno{nullptr};
    StringDecorator *password{nullptr};


signals:

};
}}

#endif // AUTHLOGIN_H
