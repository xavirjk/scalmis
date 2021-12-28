#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <QObject>
#include <QJsonObject>
#include <QtQml/QQmlListProperty>
#include <SCALMIS-LIB_global.h>
#include <data/entitycollection.h>
#include <data/entity.h>
#include <data/intdecorator.h>
#include <models/authlogin.h>
#include <data/comboselect.h>
using namespace SCALMIS::data;
namespace SCALMIS {
namespace models {
class SCALMISLIB_EXPORT Accounts : public Entity
{
    Q_OBJECT

    Q_PROPERTY(SCALMIS::data::IntDecorator *ui_pjno MEMBER pjno CONSTANT)
    Q_PROPERTY(SCALMIS::data::IntDecorator *ui_type MEMBER authType CONSTANT)
    Q_PROPERTY(SCALMIS::data::StringDecorator *ui_email MEMBER email CONSTANT)
    Q_PROPERTY(SCALMIS::data::StringDecorator *ui_password MEMBER password CONSTANT)
    Q_PROPERTY(SCALMIS::data::StringDecorator *ui_office MEMBER office CONSTANT)
    Q_PROPERTY(SCALMIS::data::StringDecorator *ui_fullname MEMBER fullname CONSTANT)
    Q_PROPERTY(SCALMIS::data::ComboSelect *ui_typeCombo MEMBER typeComboSelect CONSTANT)
public:
    explicit Accounts(QObject *parent = nullptr);
    Accounts(QObject *parent, const QJsonObject &json);
    ~Accounts();

    ComboSelect *typeComboSelect{nullptr};
    IntDecorator *authType{nullptr};
    IntDecorator *pjno{nullptr};
    StringDecorator *email{nullptr};
    StringDecorator *fullname{nullptr};
    StringDecorator *office{nullptr};
    StringDecorator *password{nullptr};
signals:
private:
    std::map<QString,int> typeModel;

};
}}

#endif // ACCOUNTS_H
