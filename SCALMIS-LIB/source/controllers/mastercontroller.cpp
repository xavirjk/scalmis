#include "mastercontroller.h"
using namespace SCALMIS::network;
namespace SCALMIS {
namespace controllers {

class MasterController::Implementation {
public:Implementation(MasterController *_MasterController):
    masterController(_MasterController)
    {
        navigationController = new NavigationController(masterController);
        authLogin = new AuthLogin(masterController);
        stock = new Stock(masterController);
        accounts = new Accounts(masterController);
        requests = new Requests(masterController);
        invoicePeriod = new InvoicePeriod(masterController);
        networkAccessManager = new NetworkAccessManager(masterController);
        serverRequest = new ServerRequest(masterController,networkAccessManager,QUrl());
        commandController = new CommandController(masterController,navigationController,authLogin,serverRequest,stock,requests,accounts,invoicePeriod);

        connect(serverRequest, &ServerRequest::messageRes, masterController, &MasterController::onMessageRes);
        connect(serverRequest, &ServerRequest::signedIn, masterController, &MasterController::onSignedIn);
        connect(serverRequest, &ServerRequest::operationSuccess, masterController, &MasterController::onOperationSuccess);
        connect(serverRequest, &ServerRequest::itemsReq, masterController, &MasterController::populateRequestItems);
        connect(serverRequest, &ServerRequest::itemDesc, masterController, &MasterController::populateDescriptives);
        connect(serverRequest, &ServerRequest::auths, masterController, &MasterController::populateAuths);
        connect(serverRequest, &ServerRequest::stockTakes, masterController, &MasterController::receivedStocks);
        connect(serverRequest, &ServerRequest::stockAsset, masterController, &MasterController::stockAssets);
        connect(serverRequest, &ServerRequest::issuedItems, masterController, &MasterController::issuedItems);
        connect(serverRequest, &ServerRequest::reqApproved, masterController, &MasterController::onReqApproved);
        connect(serverRequest, &ServerRequest::services, masterController, &MasterController::populateServices);
        connect(serverRequest, &ServerRequest::project, masterController, &MasterController::project);
        connect(serverRequest, &ServerRequest::quitApp, masterController, &MasterController::QuitApp);
        connect(serverRequest, &ServerRequest::serverVersion, masterController, &MasterController::serverVersion);
    }

    MasterController *masterController{nullptr};
    NavigationController *navigationController{nullptr};
    CommandController *commandController{nullptr};
    AuthLogin *authLogin{nullptr};
    Accounts *accounts{nullptr};
    Stock *stock{nullptr};
    Requests *requests{nullptr};
    InvoicePeriod *invoicePeriod{nullptr};
    NetworkAccessManager *networkAccessManager{nullptr};
    ServerRequest *serverRequest{nullptr};

    QString title = "SCALMIS";
    QJsonArray updates;
    QString context;
    enum MODES{DASHBOARD_MODE,REQUEST_MODE, INVOICE_MODE, USERS_MODE};
    MODES r_mode;
    const char *MODES_NAMES[4] = {"dashboard", "request", "invoice", "users"};

    bool scalmis = false;
    bool scalmis_server = false;

    QJsonObject theUpdates;

};

MasterController::MasterController(QObject *parent) : QObject(parent)
{
    implementation.reset(new Implementation(this));

}
MasterController::~MasterController(){}

NavigationController *MasterController::navigationController(){
    return implementation->navigationController;
}
CommandController *MasterController::commandController(){
    return implementation->commandController;
}

AuthLogin *MasterController::authLogin(){
    return implementation->authLogin;
}
Accounts *MasterController::accounts(){
    return implementation->accounts;
}
Stock *MasterController::stock(){
    return implementation->stock;
}
Requests *MasterController::requests(){
    return implementation->requests;
}
InvoicePeriod *MasterController::invoicePeriod(){
    return implementation->invoicePeriod;
}
const QString &MasterController::sysTitle()const{
    return implementation->title;
}
void MasterController::setContext(int context){
    switch (context) {
    case 0:
        implementation->r_mode = implementation->DASHBOARD_MODE;break;
    case 1:
        implementation->r_mode = implementation->REQUEST_MODE;break;
    case 2:
        implementation->r_mode = implementation->INVOICE_MODE;break;
    case 3:
        implementation->r_mode = implementation->USERS_MODE;break;
    default:break;
    }
}
int MasterController::getContext(){
    return implementation->r_mode;
}
void MasterController::onMessageRes(const QString message){
    implementation->commandController->resetCommands();
    emit implementation->commandController->serverResponse(message);
}
void MasterController::onSignedIn(QJsonObject body){
    implementation->commandController->setToken(body);
    emit implementation->navigationController->goAdminView();
}
void MasterController::onReqApproved(){
    implementation->commandController->getApproved(true,"false");
}
void MasterController::onOperationSuccess(){
    implementation->accounts->update({});
    implementation->stock->clearStock();
    implementation->requests->clearRequests();
    emit implementation->navigationController->goAdminDashboardView();
}
void MasterController::populateRequestItems(QJsonArray body){
    implementation->requests->requestItems->update(body);
    implementation->requests->setupItemsModel();
    if(implementation->r_mode == implementation->REQUEST_MODE)
        implementation->commandController->cBoxAuths();
}
void MasterController::populateDescriptives(QJsonArray body){
    implementation->requests->itemDescriptives->update(body);
    implementation->requests->setUpDescModel();
}
void MasterController::populateAuths(QJsonArray body){
    if(implementation->r_mode == implementation->USERS_MODE){
        emit implementation->navigationController->goRenderUsers(body);
        return;
    }
    implementation->requests->auths->update(body);
    implementation->requests->setUpAuthModel();
    if(implementation->r_mode == implementation->INVOICE_MODE){
        implementation->commandController->setContextCommands("proceed");
        emit implementation->navigationController->goRequestItem();
        return;
    }
    implementation->commandController->cboxServices();
}
void MasterController::populateServices(QJsonArray body){
    implementation->requests->requestServices->update(body);
    implementation->requests->setUpServicesModel();
    implementation->commandController->setContextCommands("next");
    emit implementation->navigationController->goRequestItem();
}
void MasterController::receivedStocks(QJsonArray body) {
    emit implementation->navigationController->goViewStock(body);
}
void MasterController::stockAssets(QJsonArray body){
    emit implementation->navigationController->goViewItems(body);
}
void MasterController::issuedItems(QJsonArray body){
    emit implementation->navigationController->goViewIssuedItems(body);
}
void MasterController::project(QJsonObject body){
    implementation->commandController->setChecked(body);
    if(body.find("project").value() == "scalmis_server"){
        emit implementation->navigationController->goCheckUpdates();
    }
    else implementation->commandController->checkUpdates("scalmis_server","project");
}
void MasterController::updates(){
    implementation->scalmis = false;
    implementation->scalmis_server = false;
    QDir root = QDir::currentPath();
    QString path = root.path()+"/_RELEASE";
    QFile file(path);
    if(!file.exists())return;
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) return;
    QTextStream in(&file);
    QString text = in.readAll();
    const QString right = text.sliced(text.indexOf("=")+2);
    QString v = right.sliced(0,right.length()-1);
    file.close();

    const QJsonArray checked = implementation->commandController->getChecked();
    if(v == checked[0].toObject().find("version").value().toString())
        implementation->scalmis = true;
    else {
        implementation->scalmis = false;
        implementation->commandController->passVersion();
    }
    implementation->commandController->checkServerVersion();

}
void MasterController::QuitApp(){
    emit killApp();
}
void MasterController::serverVersion(QString version){
    implementation->theUpdates = QJsonObject();
    const QJsonArray checked = implementation->commandController->getChecked();
    if(version == checked[1].toObject().find("version").value().toString() && implementation->scalmis)
        implementation->theUpdates = {};
    else if(!implementation->scalmis)
        implementation->theUpdates["scalmis"] = checked[0].toObject().find("version").value();
    else if(version != checked[1].toObject().find("version").value().toString())
        implementation->theUpdates["server"] = checked[1].toObject().find("version").value();
    emit viewUpdates(implementation->theUpdates);
}
}
}
