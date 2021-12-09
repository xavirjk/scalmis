#include "serverrequest.h"
#include "QJsonDocument"
#include "QStandardPaths"
#include "QCoreApplication"
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QDesktopServices>
#include <windows.h>
#include <shellapi.h>
namespace SCALMIS {
namespace network {
class ServerRequest::Implementation {
public:Implementation(ServerRequest *_serverRequest, INetworkAccessManager *_networkAccessManager, const QUrl &_uri):
        serverRequest(_serverRequest),
        netWorkAccessManager(_networkAccessManager),
        uri(_uri)
    {}
    ServerRequest* serverRequest{nullptr};
    INetworkAccessManager* netWorkAccessManager{nullptr};
    QUrl uri{};
    QNetworkReply *response{nullptr};
    QString basePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString updPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    QString fullPath = basePath + '/';

    bool isBusy() const{
        return isBusy_ ;
    }
    void setIsBusy(bool value){
        if(value != isBusy_){
            isBusy_ = value;
            emit serverRequest->isBusyChanged();
        }
    }
    bool handlingFl() const {
        return handlingFile;
    }
    bool updating () const {
        return update;
    }
    QString getV(){
        return version;
    }
    void setFileHandling(bool value){
        if(value != handlingFile){
            handlingFile = value;
        }
    }
    void setUpdate(bool value){
        if(value != update){
            update = value;
        }
    }
    void setVersion(QString v){
        version = v;
    }
private:
    bool isBusy_ {false};
    bool handlingFile{false};
    bool update{false};
    QString version = "";
};

ServerRequest::ServerRequest(QObject *parent, INetworkAccessManager *networkAccessManager, const QUrl &uri) : IServerRequest(parent)
{
    implementation.reset(new Implementation(this,networkAccessManager,uri));

}

ServerRequest::~ServerRequest(){}

void ServerRequest::executePost(const QByteArray &data, const QString &user){
    if(!implementation->netWorkAccessManager->isNetAccessible()){
        return;
    }
    implementation->setIsBusy(true);
    emit isBusyChanged();
    QNetworkRequest request;
    request.setRawHeader("Authorization",user.toLocal8Bit());
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    request.setUrl(implementation->uri);
    implementation->response =  implementation->netWorkAccessManager->post(request,data);
    handleRes();
}

void ServerRequest::executeSearch(const QString &text, const QString &searchkey){
    if(!implementation->netWorkAccessManager->isNetAccessible()){
        return;
    }
    QNetworkRequest request;
    QUrlQuery query;
    query.addQueryItem(searchkey,text);

    implementation->uri.setQuery(query);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setUrl(implementation->uri);
    implementation->response = implementation->netWorkAccessManager->get(request);
    handleRes();
}
void ServerRequest::executeQuery(bool ref, const QString &text, const QString &auth){
    QNetworkRequest request;
    request.setRawHeader("Authorization",auth.toLocal8Bit());
    QUrlQuery query;
    ref?query.addQueryItem("today","true"):query.addQueryItem("today","false");
    if(text.isEmpty())query.addQueryItem("all","{}");
    else query.addQueryItem("approved",text);
    implementation->uri.setQuery(query);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setUrl(implementation->uri);
    implementation->response = implementation->netWorkAccessManager->get(request);
    handleRes();
}
void ServerRequest::executeGet(const QString &auth, const QString &ref) {
    QNetworkRequest request;
    request.setRawHeader("Authorization",auth.toLocal8Bit());
    request.setRawHeader("ref",ref.toLocal8Bit());
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setUrl(implementation->uri);
    implementation->response = implementation->netWorkAccessManager->get(request);
    handleRes();
}
bool ServerRequest::isBusy() const{
    return implementation->isBusy();
}
void ServerRequest::fileHandling(bool status) const{
    implementation->setFileHandling(status);
}
void ServerRequest::update(bool status) const{
    implementation->setUpdate(status);
}
void ServerRequest::setUrl(const QUrl &uri) {
    if(implementation->uri != uri) {
        implementation->uri = uri;
        emit uriChanged();
    }

}
void ServerRequest::setVersion(QString v){
    implementation->setVersion(v);
}

QUrl ServerRequest::uri() const{
    return implementation->uri;
}

void ServerRequest::replyDelegate(){
    implementation->setIsBusy(false);
    emit isBusyChanged();
    disconnect(implementation->response,&QNetworkReply::finished, this,&ServerRequest::replyDelegate);
    disconnect(implementation->response,&QNetworkReply::sslErrors, this,&ServerRequest::sslErrors);

    auto statusCode = implementation->response->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    auto res = implementation->response->readAll();
    QJsonDocument jsdoc(QJsonDocument::fromJson(res));
    auto json = jsdoc.object();
    QString message = json.find("message").value().toString();
    switch (statusCode) {
    case 0:{emit messageRes("Server not available");break;}
    case 201: {
        emit messageRes(message);
        emit operationSuccess();
        break;
    }
    case 206: {
        emit messageRes(message);
        break;
    }
    case 200: {
        if(json.find("token").value().isString()){
            emit signedIn(json);
        }
        else if(message == "itemsreq") {
            emit itemsReq(json.find("items").value().toArray());
        }
        else if(message == "itemDesc") {
            emit itemDesc(json.find("descriptives").value().toArray());
        }
        else if(message =="auths") {
            emit auths(json.find("auths").value().toArray());
        }
        else if(message == "services"){
            emit services(json.find("services").value().toArray());
        }
        else if(message == "all stock"){
            emit messageRes(message);
            emit stockTakes(json.find("stock").value().toArray());
        }
        else if(message == "stock assets"){
            emit messageRes(message);
            emit stockAsset(json.find("result").value().toArray());
        }
        else if(message == "issued"){
            emit issuedItems(json.find("issued").value().toArray());
        }
        else if(message == "Request Approved"){
            emit messageRes(message);
            emit reqApproved();
        }
        else if(message == "version"){
            emit serverVersion(json.find("version").value().toString());
        }
        else if(message == "project") emit project(json.find("latest").value().toObject());
        else if(message == "Delete Success") emit messageRes(message);
        else if(message == "models success") emit modelsNumSuccess(json.find("count").value().toInt());
        break;
    }
    default: {message.isEmpty()? emit messageRes(res):emit messageRes(message); break;}
    }
}

void ServerRequest::sslErrors(const QList<QSslError> &errors){
    QString sslError;
    for(const auto& error : errors){
        sslError += error.errorString() + "\n";
    }
    qDebug()<<"sslError"<<sslError;
    emit error(sslError);
}
void ServerRequest::mimeDelegate(){
    disconnect(implementation->response,&QNetworkReply::finished, this,&ServerRequest::replyDelegate);
    disconnect(implementation->response,&QNetworkReply::sslErrors, this,&ServerRequest::sslErrors);
    disconnect(implementation->response,&QIODevice::readyRead,this,&ServerRequest::mimeDelegate);
    implementation->setFileHandling(false);
    QByteArray data = implementation->response->readAll();
    auto statusCode = implementation->response->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(statusCode == 404) {
         QJsonDocument jsdoc(QJsonDocument::fromJson(data));
         emit messageRes(jsdoc.object().find("message").value().toString());
    }
    else if(statusCode != 200) emit messageRes(data);
    else saveFile(data);
}
void ServerRequest::saveFile(const QByteArray &data){
    bool temp = implementation->updating();
    implementation->setUpdate(false);
    QString path, dirPath;
    QDir *dir;
    dirPath = implementation->updPath+"/scalmis";
    if(temp)
        path =implementation->updPath+"/scalmis/scalmis.zip";
    else {
        path = implementation->fullPath + "Data/dt.pdf";
        dirPath = implementation->basePath+"/Data";
    }
    dir = new QDir(dirPath);
    QFile file(path);
    if(!dir->exists()) dir->mkdir(dirPath);
    if (!file.open(QIODevice::WriteOnly)) {
        emit messageRes("file not open for writing , might be in use by another App");
        fprintf(stderr, "Could not open %s for writing: %s\n",
                qPrintable(implementation->fullPath),
                qPrintable(file.errorString()));
        return;
    }
    file.write(data);
    file.close();
    if(temp) {
        dir = new QDir();
        file.setFileName(dir->currentPath()+"/s_update.exe");
        if(file.exists()){
            QString args =implementation->getV()+" "+"update"+" "+"scalmis";
            HINSTANCE  hres;
            hres = ShellExecute(nullptr, L"runas", file.fileName().toStdWString().c_str(), args.toStdWString().c_str(), nullptr, SW_SHOW);
            emit quitApp();
        }
        return;
    }
    else QDesktopServices::openUrl(QUrl(path,QUrl::TolerantMode));
}
void ServerRequest::handleRes(){
    if(implementation->response != nullptr){
        connect(implementation->response,&QNetworkReply::sslErrors, this,&ServerRequest::sslErrors);
        if(implementation->handlingFl()) {
            connect(implementation->response,&QNetworkReply::finished,this,&ServerRequest::mimeDelegate);
        }
        else connect(implementation->response,&QNetworkReply::finished, this,&ServerRequest::replyDelegate);
    }
}

}}

