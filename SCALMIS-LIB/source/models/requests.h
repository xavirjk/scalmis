#ifndef REQUESTS_H
#define REQUESTS_H

#include <QObject>
#include <QJsonObject>
#include <QtQml/QQmlListProperty>
#include <SCALMIS-LIB_global.h>
#include <data/entitycollection.h>
#include <data/entity.h>
#include <data/comboselect.h>
#include <models/stockitem.h>
#include <models/service.h>
#include <models/requestitem.h>
#include <models/itemdescriptives.h>
#include <models/accounts.h>
using namespace SCALMIS::data;
namespace SCALMIS {
namespace models {
class SCALMISLIB_EXPORT Requests : public Entity
{
    Q_OBJECT

    Q_PROPERTY(SCALMIS::data::StringDecorator *ui_Officer MEMBER officer CONSTANT)
    Q_PROPERTY(SCALMIS::data::StringDecorator *ui_Office MEMBER office CONSTANT)
    Q_PROPERTY(SCALMIS::data::IntDecorator *ui_toggle MEMBER toggle NOTIFY toggleChanged)
    Q_PROPERTY(SCALMIS::data::ComboSelect* ui_itemsComboSelect MEMBER itemsComboSelect NOTIFY itemsComboChanged)
    Q_PROPERTY(SCALMIS::data::ComboSelect* ui_descComboSelect MEMBER descComboSelect NOTIFY descComboChanged)
    Q_PROPERTY(SCALMIS::data::ComboSelect* ui_authsComboSelect MEMBER authsComboSelect NOTIFY authsComboChanged)
    Q_PROPERTY(SCALMIS::data::ComboSelect* ui_srvComboSelect MEMBER srvComboSelect NOTIFY srvComboChanged)
    Q_PROPERTY(SCALMIS::data::ComboSelect* ui_membersComboSelect MEMBER membersComboSelect NOTIFY membersComboChanged)
    Q_PROPERTY(QQmlListProperty<SCALMIS::models::StockItem> ui_requests READ ui_requests NOTIFY requestsChanged)
    Q_PROPERTY(QQmlListProperty<SCALMIS::models::Service> ui_srvrequests READ ui_srvrequests NOTIFY srvRequestsChanged)
public:
    explicit Requests(QObject *parent = nullptr);
    Requests(QObject *parent, const QJsonObject &json);
    ~Requests();

    void setupItemsModel();
    void setUpDescModel();
    void setUpAuthModel();
    void setUpServicesModel();
    QString getItemId(const QString &item);
    QString getServiceId(const QString &service);
    void clearRequests();

    ComboSelect *itemsComboSelect{nullptr};
    ComboSelect *descComboSelect{nullptr};
    ComboSelect *authsComboSelect{nullptr};
    ComboSelect *srvComboSelect{nullptr};
    ComboSelect *membersComboSelect{nullptr};

    StringDecorator *officer{nullptr};
    StringDecorator *office{nullptr};
    IntDecorator *toggle{nullptr};
    EntityCollection<RequestItem > *requestItems{nullptr};
    EntityCollection<Service> *requestServices{nullptr};
    EntityCollection<ItemDescriptives> *itemDescriptives{nullptr};
    EntityCollection<Accounts> *auths{nullptr};
    EntityCollection<StockItem> *requests{nullptr};
    EntityCollection<Service> *srvrequests{nullptr};
    QQmlListProperty<SCALMIS::models::StockItem> ui_requests();
    QQmlListProperty<SCALMIS::models::Service> ui_srvrequests();

public slots:
    void appendItem();
    void appendService();
    void removeService();
    void setServiceModels();
    void removeItem();
    void setmodels();
    void emitToggled();
    void officeMembers();
signals:
    void requestsChanged();
    void srvRequestsChanged();
    void srvComboChanged();
    void itemsComboChanged();
    void descComboChanged();
    void authsComboChanged();
    void toggleChanged();
    void membersComboChanged();
private:
    std::map<QString,int> itemsModel;
    std::map<QString,int> descModel;
    std::map<QString, int> authsModel;
    std::map<QString, int> servicesModel;
    std::map<QString, int> members;

};
}}

#endif // REQUESTS_H
