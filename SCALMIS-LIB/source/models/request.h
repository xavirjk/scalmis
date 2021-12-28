#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QJsonObject>
#include <QtQml/QQmlListProperty>
#include <SCALMIS-LIB_global.h>
#include <data/entitycollection.h>
#include <data/entity.h>
#include <data/stringdecorator.h>
//#include <data/comboselect.h>
//#include <models/requestitem.h>
//#include <models/itemdescriptives.h>
//#include <models/accounts.h>
using namespace SCALMIS::data;
namespace SCALMIS {
namespace models {
class SCALMISLIB_EXPORT Request : public Entity
{
    Q_OBJECT

    /*Q_PROPERTY(SCALMIS::data::StringDecorator *ui_Officer MEMBER fullname CONSTANT)
    Q_PROPERTY(SCALMIS::data::StringDecorator *ui_Office MEMBER office CONSTANT)*/
    Q_PROPERTY(SCALMIS::data::StringDecorator *ui_quantity MEMBER quantity CONSTANT)
    /*Q_PROPERTY(SCALMIS::data::ComboSelect* ui_itemsComboSelect MEMBER itemsComboSelect NOTIFY itemsComboChanged)
    Q_PROPERTY(SCALMIS::data::ComboSelect* ui_descComboSelect MEMBER descComboSelect NOTIFY descComboChanged)
    Q_PROPERTY(SCALMIS::data::ComboSelect* ui_authsComboSelect MEMBER authsComboSelect NOTIFY authsComboChanged)*/
public:
    explicit Request(QObject *parent = nullptr);
    Request(QObject *parent,const QJsonObject &json);
    ~Request();

    /*void setupItemsModel();
    void setUpDescModel();
    void setUpAuthModel();
    QString getItemId(const QString &item);

    ComboSelect *itemsComboSelect{nullptr};
    ComboSelect *descComboSelect{nullptr};
    ComboSelect *authsComboSelect{nullptr};
    StringDecorator *fullname{nullptr};
    StringDecorator *office{nullptr};*/
    StringDecorator *quantity{nullptr};


    /*EntityCollection<RequestItem > *requestItems{nullptr};
    EntityCollection<ItemDescriptives> *itemDescriptives{nullptr};
    EntityCollection<Accounts> *auths{nullptr};

signals:
    void itemsComboChanged();
    void descComboChanged();
    void authsComboChanged();
private:
    std::map<QString,int> itemsModel;
    std::map<QString,int> descModel;
    std::map<QString, int> authsModel;*/

};
}}
#endif // REQUEST_H
