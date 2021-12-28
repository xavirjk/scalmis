#include "commandcontroller.h"
#include <QJsonDocument>
#include <QSslSocket>

using namespace SCALMIS::network;
using namespace SCALMIS::flow;

namespace SCALMIS {
namespace controllers {
class CommandController::Implementation {
public: Implementation(CommandController *_CommandController, NavigationController *_Navigator, AuthLogin *_AuthLogin, IServerRequest *_iServerRequest, Stock *_Stock, Requests *_Requests, Accounts *_Accounts, InvoicePeriod *_InvoicePeriod):
        commandController(_CommandController),
        navigationController(_Navigator),
        authLogin(_AuthLogin),
        serverRequest(_iServerRequest),
        stock(_Stock),
        requests(_Requests),
        accounts(_Accounts),
        invoicePeriod(_InvoicePeriod)

    {
        newStock = new Commands(commandController,"","Create");
        officeSel = new Commands(commandController,"","Item");
        reqItems = new Commands(commandController,"","Request");
        saveItem = new Commands(commandController,"","Save");
        deleteItem = new Commands(commandController,"","Delete");
        createUser = new Commands(commandController,"","Create");
        updateStock = new Commands(commandController, "", "Update");
        invoiceProceed = new Commands(commandController, "","Proceed");
        generateInv = new Commands(commandController, "","Generate");
        newService = new Commands(commandController, "", "Create");
        reqService = new Commands(commandController, "", "Service");
        postsrvReq = new Commands(commandController, "", "Post Request");
        saveUser = new Commands(commandController, "","Save");
        deleteUser = new Commands(commandController, "", "Delete");
        changePassword = new Commands(commandController, "", "Reset");
        connect(newStock,&Commands::executed,commandController,&CommandController::newStock);
        connect(newService, &Commands::executed, commandController, &CommandController::newService);
        connect(officeSel,&Commands::executed,commandController,&CommandController::displayReqItemsPage);
        connect(reqItems, &Commands::executed,commandController,&CommandController::requestItems);
        connect(deleteItem, &Commands::executed,commandController, &CommandController::deleteItem);
        connect(saveItem, &Commands::executed,commandController, &CommandController::saveItem);
        connect(createUser, &Commands::executed,commandController, &CommandController::createUser);
        connect(updateStock, &Commands::executed, commandController, &CommandController::saveItem);
        connect(invoiceProceed, &Commands::executed, commandController, &CommandController::proceedToGetInvoice);
        connect(generateInv, &Commands::executed,commandController, &CommandController::generateInvoicePeriod);
        connect(reqService, &Commands::executed, commandController,&CommandController::displayReqServicePage);
        connect(postsrvReq, &Commands::executed, commandController, &CommandController::postRequestService);
        connect(saveUser, &Commands::executed, commandController,&CommandController::saveUser);
        connect(deleteUser,&Commands::executed, commandController, &CommandController::initiateDeleteUser);
        connect(changePassword, &Commands::executed, commandController, &CommandController::ResetPassword);
    }
    CommandController *commandController{nullptr};
    NavigationController *navigationController{nullptr};
    AuthLogin *authLogin{nullptr};
    IServerRequest *serverRequest{nullptr};
    Stock *stock{nullptr};
    Requests *requests{nullptr};
    Accounts *accounts{nullptr};
    InvoicePeriod *invoicePeriod{nullptr};
    QString base = "http://localhost:3500/";
    //QString base = "http://10.41.103.228:3500/";
    //QString updates = "http://localhost:3700/";
    QString updates = "http://apps-v.herokuapp.com/";
    QString auth = base+"auth/sign-in/";
    QString _public = base+"public/";
    QString admin = base+"admin/";
    QString user = base+"user/";

    QString context;
    QJsonObject apprContext;
    QJsonObject updateRefStock;

    QJsonArray checked;

    QJsonObject authToken;
    QList<Commands*> contextCommands{};
    Commands *newStock, *officeSel,*reqItems, *saveItem, *deleteItem, *createUser, *updateStock,*invoiceProceed,*generateInv,*newService, *reqService, *postsrvReq, *saveUser, *deleteUser, *changePassword;
};

CommandController::CommandController(QObject *parent, NavigationController *navigator, AuthLogin *authLogin, IServerRequest *iServerRequest, Stock *stock, Requests *requests, Accounts *accounts, InvoicePeriod *invoicePeriod) : QObject(parent)
{
    implementation.reset(new Implementation(this, navigator, authLogin,iServerRequest, stock, requests,accounts,invoicePeriod));
}
CommandController::~CommandController(){}
void CommandController::setToken(QJsonObject &json){
    implementation->authToken = json;
}
void CommandController::setContextCommands(QString context){
    resetCommands();
    implementation->contextCommands.clear();
    if(context == "new stock")implementation->contextCommands.append(implementation->newStock);
    else if(context == "next"){
        implementation->contextCommands.append(implementation->officeSel);
        implementation->contextCommands.append(implementation->reqService);
    }
    else if(context == "request-items")implementation->contextCommands.append(implementation->reqItems);
    else if(context == "req-services")implementation->contextCommands.append(implementation->postsrvReq);
    else if(context == "item edit"){
        implementation->contextCommands.append(implementation->saveItem);
        implementation->contextCommands.append(implementation->deleteItem);
    }
    else if(context == "create-profile")implementation->contextCommands.append(implementation->createUser);
    else if(context == "edit-user"){
        implementation->contextCommands.append(implementation->saveUser);
        implementation->contextCommands.append(implementation->deleteUser);
    }
    else if(context == "Change-password")implementation->contextCommands.append(implementation->changePassword);
    else if(context == "item update") implementation->contextCommands.append(implementation->updateStock);
    else if(context == "proceed") implementation->contextCommands.append(implementation->invoiceProceed);
    else if(context == "generate") implementation->contextCommands.append(implementation->generateInv);
    else if(context == "new service") implementation->contextCommands.append(implementation->newService);
    implementation->context = context;
    emit contextCommandsChanged();
}
QQmlListProperty<Commands> CommandController::contextCommands(){
    return QQmlListProperty(this, &implementation->contextCommands);
}
void CommandController::signin(){
    implementation->serverRequest->setUrl(implementation->auth+"admin");
    QJsonDocument doc(implementation->authLogin->getCompleteJson());
    implementation->serverRequest->executePost(doc.toJson(),implementation->authLogin->id());
}

void CommandController::signout_admin(){
    implementation->stock->clearStock();
    implementation->authLogin->pjno->setVal(0);
    implementation->authLogin->password->setVal("");
    implementation->authToken = {};
    emit implementation->navigationController->goLogoutAdmin();
}
void CommandController::cBoxItems(){
    implementation->serverRequest->setUrl(implementation->_public+ "items-in-stock/");
    implementation->serverRequest->executeGet(implementation->authToken.find("token")->toString(),"");
}
void CommandController::cBoxAuths(){
    implementation->serverRequest->setUrl(implementation->admin+"get-auths/");
    implementation->serverRequest->executeGet(implementation->authToken.find("token")->toString(),"");
}
void CommandController::cBoxDesc(const QString &item){
    implementation->serverRequest->setUrl(implementation->_public+ "item-descriptives/");
    implementation->serverRequest->executeGet(implementation->authToken.find("token")->toString(),implementation->requests->getItemId(item));
}
void CommandController::cboxServices(){
    implementation->serverRequest->setUrl(implementation->_public+ "get-services/");
    implementation->serverRequest->executeGet(implementation->authToken.find("token")->toString(),"");
}
void CommandController::newStock(){
    if(!implementation->stock->stockItems->derivedEntities().size()){
        emit serverResponse("Cannot Submit Uninitialized Stock");
        return;
    }
    for(int i= 0; i < implementation->stock->stockItems->derivedEntities().length(); i++){
        if(!(implementation->stock->stockItems->derivedEntities().at(i)->item->inputValid()
             &&implementation->stock->stockItems->derivedEntities().at(i)->code->inputValid())){
            emit serverResponse("err submitting invalid item,code or Empty fields");
            return;
        }
    }
    implementation->serverRequest->setUrl(implementation->admin+"new-stock/");
    QJsonDocument doc;
    if(implementation->context == "new stock")
        doc.setArray(implementation->stock->getCompleteJson().find("stockItems")->toArray());
    else {
        QJsonObject obj;
        obj.insert("stock",implementation->updateRefStock);
        obj.insert("data",implementation->stock->getCompleteJson().find("stockItems")->toArray());
        doc.setObject(obj);
    }
    implementation->serverRequest->executePost(doc.toJson(),implementation->authToken.find("token")->toString());
}
void CommandController::newService(){
    if(!implementation->stock->service->derivedEntities().size()){
        emit serverResponse("Cannot Submit Uninitialized");
        return;
    }
    for(int i= 0; i < implementation->stock->service->derivedEntities().length(); i++){
        if(!(implementation->stock->service->derivedEntities().at(i)->service->inputValid()
             &&implementation->stock->service->derivedEntities().at(i)->code->inputValid())){
            emit serverResponse("err submitting invalid service code, service  or Empty fields");
            return;
        }
    }
    implementation->serverRequest->setUrl(implementation->admin+"new-service/");
    QJsonDocument doc;
    doc.setArray(implementation->stock->getCompleteJson().find("service")->toArray());
    implementation->serverRequest->executePost(doc.toJson(), implementation->authToken.find("token")->toString());

}
void CommandController::displayReqItemsPage(){
    if(checkOfficeValidity(false)){
        setContextCommands("request-items");
        emit implementation->navigationController->goSelectItems();
    }
}
void CommandController::displayReqServicePage(){
    if(checkOfficeValidity(false)){
        setContextCommands("req-services");
        emit implementation->navigationController->goSelectServices();
    }
}
void CommandController::proceedToGetInvoice(){
    if(checkOfficeValidity(true)){
        setContextCommands("generate");
        emit implementation->navigationController->goGetDates();
    }
}
void CommandController::getStockTakes(){
    implementation->serverRequest->setUrl(implementation->admin+"stock-entry/");
    implementation->serverRequest->executeGet(implementation->authToken.find("token")->toString(),"");
}
void CommandController::requestItems(){
    int len = implementation->requests->requests->derivedEntities().size();
    if(!len){
        emit serverResponse("Cannot Request Uninitialized");
        return;
    }
    if(!(implementation->requests->requests->derivedEntities().last()->item->inputValid())){
        emit serverResponse("attempting to submit Null");
        return;
    }
    requestHelper(true);
}
void CommandController::postRequestService(){
    int len = implementation->requests->srvrequests->derivedEntities().size();
    if(!len){
        emit serverResponse("Cannot Request Uninitialized");
        return;
    }
    if(!(implementation->requests->srvrequests->derivedEntities().last()->service->inputValid())){
          emit serverResponse("attempting to submit Null");
          return;
    }
    requestHelper(false);
}
void CommandController::getStockData(const QString ObjId){
    implementation->serverRequest->setUrl(implementation->admin+"stock/assets/");
    implementation->serverRequest->executeGet(implementation->authToken.find("token")->toString(), ObjId);

}
void CommandController::setUpStockItems(const QJsonArray json, const QString &context ){
    if(context == "item edit" || context == "item update")setContextCommands(context);
    if(implementation->context != "new stock"){
        implementation->stock->stockItems->update(json);
        emit implementation->stock->stockChanged();
    }
    setContextCommands(context);
    emit implementation->navigationController->goCreateNewStockTake();
}
void CommandController::deleteItem(){
    implementation->serverRequest->setUrl(implementation->admin+"delete/stock-item/");
    QJsonObject obj;
    obj.insert("id",implementation->stock->stockItems->derivedEntities().at(0)->id());
   implementation->serverRequest->executePost(QJsonDocument(obj).toJson(),implementation->authToken.find("token")->toString());
}
void CommandController::saveItem(){
    implementation->serverRequest->setUrl(implementation->admin+"save/stock-item/");
    QJsonObject obj;
    if(implementation->context == "item update") obj.insert("update",true);
    obj.insert("id",implementation->stock->stockItems->derivedEntities().at(0)->id());
    obj.insert("item",implementation->stock->getCompleteJson());
    implementation->serverRequest->executePost(QJsonDocument(obj).toJson(),implementation->authToken.find("token")->toString());

}
void CommandController::createUser(){
    implementation->accounts->password->setVal("");
    if(!validateAccount()){
        emit serverResponse("Credentials Failed to Meet Constraints");
        return;
    }
    if(implementation->accounts->authType->inputVal()){
        implementation->serverRequest->setUrl(implementation->admin+"create-user/admin");
    }else
        implementation->serverRequest->setUrl(implementation->admin+"create-user/user");
    implementation->serverRequest->executePost(QJsonDocument(implementation->accounts->getCompleteJson()).toJson(),
                                               implementation->authToken.find("token")->toString());
}
QJsonArray CommandController::modifyRequest(QJsonArray requests, bool isItem){
    QJsonArray newArray;
    for(QJsonValue val: requests){
        QJsonObject obj;
        obj.insert("quantity",val.toObject().find("amountAdded").value());
        if(isItem){
            obj.insert("itemId",implementation->requests->getItemId(val.toObject().find("item").value().toString()));
            obj.insert("description",val.toObject().find("description").value());
        }
        else obj.insert("itemId", implementation->requests->getServiceId(val.toObject().find("item").value().toString()));
        newArray.append(obj);
    }
    return newArray;
}
void CommandController::requestHelper(bool isItem){
    QJsonObject refMember, request;
    if(implementation->requests->officer->inputVal().toInt())refMember.insert("pjno",implementation->requests->officer->inputVal());
    else refMember.insert("fullname",implementation->requests->officer->inputVal());
    refMember.insert(implementation->requests->office->key(),implementation->requests->office->inputVal());
    request.insert("isItem",isItem);
    request.insert("refMember",refMember);
    if(isItem)
        request.insert("items",modifyRequest(implementation->requests->getCompleteJson().find("Requests")->toArray(),isItem));
    else
        request.insert("items",modifyRequest(implementation->requests->getCompleteJson().find("SrvRequests")->toArray(),isItem));
    implementation->serverRequest->setUrl(implementation->_public+"request-items/");
    implementation->serverRequest->executePost(QJsonDocument(request).toJson(),
                                               implementation->authToken.find("token")->toString());
}
void CommandController::getApproved(bool ref, QString text){
    implementation->apprContext["ref"] = ref;
    implementation->apprContext["text"] = text;
    implementation->serverRequest->setUrl(implementation->_public+"items/issued/");
    implementation->serverRequest->executeQuery(ref,text,implementation->authToken.find("token")->toString());
}

void CommandController::useApprContext(){
    getApproved(implementation->apprContext["ref"].toBool(),implementation->apprContext["text"].toString());
}
void CommandController::setUpdateStockId(const QString &id){
    implementation->updateRefStock["id"] = id;
}

void CommandController::downloadStock(){
    implementation->serverRequest->setUrl(implementation->admin+"generate/all-items/");
    implementation->serverRequest->fileHandling(true);
    implementation->serverRequest->update(false);
    implementation->serverRequest->executeGet(implementation->authToken.find("token")->toString(),"");
}
void CommandController::generateInvoice(const QJsonObject &obj){
    implementation->serverRequest->setUrl(implementation->admin+"generate/invoice/");
    implementation->serverRequest->fileHandling(true);
    implementation->serverRequest->update(false);
    implementation->serverRequest->executePost(QJsonDocument(obj).toJson(),
                                               implementation->authToken.find("token")->toString());
}
void CommandController::generateInvoicePeriod(){
    implementation->serverRequest->setUrl(implementation->admin+"generate/invoice-period/");
    implementation->serverRequest->fileHandling(true);
    implementation->serverRequest->update(false);
    QJsonObject obj = implementation->invoicePeriod->getCompleteJson();
    obj["office"] = implementation->requests->office->inputVal().trimmed();
    if(implementation->requests->officer->inputVal().toInt())
        obj["pjno"] = implementation->requests->officer->inputVal().trimmed();
    else obj["fullname"] = implementation->requests->officer->inputVal().trimmed();
    implementation->serverRequest->executePost(QJsonDocument(obj).toJson(),
                                               implementation->authToken.find("token")->toString());
}

bool CommandController::checkOfficeValidity(bool allowEmpty){
    if(implementation->requests->office->inputValid() && implementation->requests->officer->inputValid()){
        return true;
    }
    if(allowEmpty) return true;
    emit serverResponse("invalid Selection");
    return false;  
}
void CommandController::doApproval(bool approval, QString objId) {
    implementation->serverRequest->setUrl(implementation->admin+ "approve-request/");
    QJsonObject obj;
    obj["id"] = objId;
    obj["approve"] = approval;
    implementation->serverRequest->executeGet(implementation->authToken.find("token")->toString(),
                                              QJsonDocument(obj).toJson(QJsonDocument::Compact));
}
QString CommandController::getContext(){
    return implementation->context;
}
void CommandController::saveUser(){
    if(!validateAccount()){
        emit serverResponse("Credentials fail to Meet Constraints");
        return;
    }
    implementation->serverRequest->setUrl(implementation->admin+"save-user/");;
    QJsonObject obj1, obj2;
    obj1["type"] = implementation->accounts->authType->inputVal();
    obj1["id"] = implementation->accounts->id();
    obj2["type"]=obj1;
    obj2["data"]=implementation->accounts->getCompleteJson();
    implementation->serverRequest->executePost(QJsonDocument(obj2).toJson()
                                               ,implementation->authToken.find("token")->toString());
}
void CommandController::initiateDeleteUser(){
    QJsonObject obj = implementation->accounts->getCompleteJson();
    obj["_id"] = implementation->accounts->id();
    editUser(obj, true);
}
void CommandController::changePassword(QJsonObject user){
    implementation->accounts->update(user);
    setContextCommands("Change-password");
    implementation->accounts->password->setVal("");
    emit implementation->navigationController->goCreateNewUser();
}
void CommandController::ResetPassword(){
    if(!implementation->accounts->password->inputValid()){
        emit serverResponse("please create A strong Password");return;
    }
    implementation->serverRequest->setUrl(implementation->_public+"reset-password/");
    QJsonObject obj;
    obj["password"] = implementation->accounts->password->inputVal();
    obj["id"] = implementation->accounts->id();
    implementation->serverRequest->executePost(QJsonDocument(obj).toJson(),
                                               implementation->authToken.find("token")->toString());
}
void CommandController::editUser(QJsonObject user, bool del){
    if(!del){
        implementation->accounts->update(user);
        if(user.find("__t").value() == "Admin")
            implementation->accounts->authType->setVal(1);
        else implementation->accounts->authType->setVal(0);
        setContextCommands("edit-user");
        implementation->accounts->password->setVal("");
        emit implementation->navigationController->goCreateNewUser();
        return;
    }
    implementation->serverRequest->setUrl(implementation->admin+"delete-user/");
    implementation->serverRequest->executePost(QJsonDocument(user).toJson(),
                                               implementation->authToken.find("token")->toString());
}
bool CommandController::validateAccount(){
    if(implementation->accounts->pjno->inputVal() >= 10000
            &&implementation->accounts->email->inputValid()
            &&implementation->accounts->fullname->inputValid()
            &&implementation->accounts->office->inputValid())return true;
    return false;
}
void CommandController::resetCommands(){
    for(Commands *command: implementation->contextCommands){
        command->reset();
    }
}
void CommandController::checkUpdates(QString text, QString key){
    if(text =="scalmis")implementation->checked = {};
    implementation->serverRequest->setUrl(implementation->updates+"public/specified/");
    implementation->serverRequest->executeSearch(text,key);
}
QJsonArray CommandController::getChecked(){
    return implementation->checked;
}
void CommandController::setChecked(QJsonObject update){
    implementation->checked.append(update);
}
void CommandController::downloadUpdate(int app){
    int  len = implementation->checked[app].toObject().find("update")->toArray().size();
    QString path = implementation->checked[app].toObject().find("update")->toArray()[len-1].toString();
    implementation->serverRequest->setUrl(path);
    if(!app){
        implementation->serverRequest->fileHandling(true);
        implementation->serverRequest->update(true);
        implementation->serverRequest->executeGet("","");
    }
    else {
        QJsonObject obj;
        obj["url"] = implementation->serverRequest->uri().url();
        implementation->serverRequest->setUrl(implementation->admin+"update/server/");
        implementation->serverRequest->executePost(QJsonDocument(obj).toJson(),
                                                   implementation->authToken.find("token")->toString());
    }
}
void CommandController::checkServerVersion(){
    implementation->serverRequest->setUrl(implementation->admin+"server/version/");
    implementation->serverRequest->executeGet(implementation->authToken.find("token")->toString(),"");
}
void CommandController::passVersion(){
    implementation->serverRequest->setVersion(implementation->checked[0].toObject().find("version").value().toString());
}
}}
