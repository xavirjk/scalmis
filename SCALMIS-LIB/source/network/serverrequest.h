#ifndef SERVERREQUEST_H
#define SERVERREQUEST_H

#include <QObject>
#include <QScopedPointer>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include "SCALMIS-LIB_global.h"
#include "network/IServerRequest.h"
#include "network/inetworkaccessmanager.h"

namespace SCALMIS{
namespace network {

class SCALMISLIB_EXPORT ServerRequest : public IServerRequest
{
    Q_OBJECT
public:
    explicit ServerRequest(QObject *parent = nullptr, INetworkAccessManager *networkAccessManager = nullptr, const QUrl &uri = QUrl());
    ~ServerRequest();

    void handleRes();
    void saveFile(const QByteArray &data);
    void executeGet(const QString &auth, const QString &ref) override;
    void executePost(const QByteArray &data, const QString &user) override;
    void executeQuery(bool ref,const QString &text,const QString &auth) override;
    void executeSearch(const QString &text, const QString &searchkey) override;
    bool isBusy() const override;
    void fileHandling(bool status) const override;
    void update(bool status) const override;
    void setUrl(const QUrl &uri) override;
    void setVersion(QString v)override;
    QUrl uri() const override;

signals:
    void uriChanged();
    void isBusyChanged();
    void error(QString error);
    void requestComplete();
    void operationSuccess();
    void signedIn(QJsonObject body);
    void itemsReq(QJsonArray body);
    void itemDesc(QJsonArray body);
    void services(QJsonArray body);
    void auths(QJsonArray body);
    void caseFlUpdateSuccess();
    void stockTakes(QJsonArray body);
    void messageRes(const QString message);
    void modelsNumSuccess(const int count);
    void stockAsset(QJsonArray body);
    void issuedItems(QJsonArray body);
    void fileData(const QByteArray &bytes);
    void reqApproved();
    void project(QJsonObject body);
    void quitApp();
    //void evokeServerUpdate();
    void serverVersion(QString version);

private slots:
    void replyDelegate();
    void mimeDelegate();
    void sslErrors(const QList<QSslError>& errors);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

};

}
}


#endif // SERVERREQUEST_H
