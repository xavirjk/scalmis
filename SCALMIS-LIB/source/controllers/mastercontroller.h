#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include "SCALMIS-LIB_global.h"
#include "controllers/navigationcontroller.h"
#include "controllers/commandcontroller.h"
#include "network/networkaccessmanager.h"
#include "network/serverrequest.h"
#include "models/authlogin.h"
#include "models/accounts.h"
#include "models/stock.h"
#include "models/requests.h"
#include "models/invoiceperiod.h"

using namespace SCALMIS::models;

namespace SCALMIS {
namespace controllers {

class SCALMISLIB_EXPORT MasterController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString ui_title READ sysTitle CONSTANT)
    Q_PROPERTY(SCALMIS::controllers::NavigationController* ui_navigator READ navigationController CONSTANT)
    Q_PROPERTY(SCALMIS::controllers::CommandController* ui_commander READ commandController CONSTANT)
    Q_PROPERTY(SCALMIS::models::AuthLogin* ui_authLogin READ authLogin CONSTANT)
    Q_PROPERTY(SCALMIS::models::Accounts* ui_accounts READ accounts CONSTANT)
    Q_PROPERTY(SCALMIS::models::Stock* ui_stock READ stock CONSTANT)
    Q_PROPERTY(SCALMIS::models::Requests* ui_requests READ requests CONSTANT)
    Q_PROPERTY(SCALMIS::models::InvoicePeriod* ui_invoicePeriod READ invoicePeriod CONSTANT)
public:
    explicit MasterController(QObject *parent = nullptr);
    ~MasterController();

    NavigationController *navigationController();
    CommandController *commandController();
    AuthLogin *authLogin();
    Accounts *accounts();
    Stock *stock();
    Requests *requests();
    InvoicePeriod *invoicePeriod();

public slots:
    void setContext(int context);
    void onMessageRes(const QString message);
    void onSignedIn(QJsonObject body);
    void onOperationSuccess();
    void populateRequestItems(QJsonArray body);
    void populateDescriptives(QJsonArray body);
    void populateAuths(QJsonArray body);
    void populateServices(QJsonArray body);
    void receivedStocks(QJsonArray body);
    void stockAssets(QJsonArray body);
    void issuedItems(QJsonArray body);
    void onReqApproved();
    const QString &sysTitle()const;
    int getContext();
    void project(QJsonObject body);
    void updates();
    void QuitApp();
    void serverVersion(QString version);

signals:
    void killApp();
    void viewUpdates(QJsonObject upds);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

};
}

}

#endif // MASTERCONTROLLER_H
