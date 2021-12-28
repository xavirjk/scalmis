#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <SCALMIS-LIB_global.h>
#include <QScopedPointer>

#include <controllers/navigationcontroller.h>
#include <flow/commands.h>
#include <network/IServerRequest.h>
#include <models/authlogin.h>
#include <models/stock.h>
#include <models/requests.h>
#include <models/accounts.h>
#include <models/invoiceperiod.h>
#include <validators/validators.h>

using namespace SCALMIS::models;
namespace SCALMIS {
namespace controllers {
class SCALMISLIB_EXPORT CommandController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<SCALMIS::flow::Commands> ui_contextCommands READ contextCommands NOTIFY contextCommandsChanged)
public:
    explicit CommandController(QObject *parent = nullptr, NavigationController *navigator = nullptr, AuthLogin *authLogin = nullptr, network::IServerRequest *iServerRequest = nullptr, Stock *stock = nullptr, Requests *requests = nullptr, Accounts *accounts = nullptr, InvoicePeriod *invoicePeriod = nullptr);
    ~CommandController();

    QQmlListProperty<flow::Commands> contextCommands();
    void setToken(QJsonObject &json);
    QJsonArray modifyRequest(QJsonArray requests, bool isItem);
    void requestHelper(bool isItem);
    void setChecked(QJsonObject update);
    QJsonArray getChecked();
    bool checkOfficeValidity(bool allowEmpty);
    void checkServerVersion();
    void passVersion();
public slots:
    void resetCommands();
    void signin();
    void signout_admin();
    void newStock();
    void newService();
    void displayReqItemsPage();
    void displayReqServicePage();
    void requestItems();
    void setContextCommands(QString context);
    void cBoxItems();
    void cBoxDesc(const QString &item);
    void cBoxAuths();
    void cboxServices();
    void getStockTakes();
    void getStockData(const QString ObjId);
    void setUpStockItems(const QJsonArray json, const QString &context);
    void setUpdateStockId(const QString &updateId);
    void saveItem();
    void deleteItem();
    void createUser();
    void getApproved(bool ref, QString text);
    void doApproval(bool approval, QString objId);
    void downloadStock();
    void generateInvoice(const QJsonObject &obj);
    void proceedToGetInvoice();
    void generateInvoicePeriod();
    void useApprContext();
    QString getContext();
    void postRequestService();
    void initiateDeleteUser();
    void saveUser();
    void editUser(QJsonObject user , bool del);
    void changePassword(QJsonObject user);
    void ResetPassword();
    bool validateAccount();
    void checkUpdates(QString text, QString key);
    void downloadUpdate(int app);
private:
    class Implementation;
    QScopedPointer<Implementation> implementation;


signals:
    void serverResponse(const QString message);
    void contextCommandsChanged();

};

}
}


#endif // COMMANDCONTROLLER_H
