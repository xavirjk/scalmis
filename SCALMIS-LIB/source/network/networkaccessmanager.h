#ifndef NETWORKACCESSMANAGER_H
#define NETWORKACCESSMANAGER_H

#include <QObject>
#include <QScopedPointer>
#include <QNetworkAccessManager>
#include <SCALMIS-LIB_global.h>
#include "network/inetworkaccessmanager.h"

namespace SCALMIS {
namespace network {

class SCALMISLIB_EXPORT NetworkAccessManager :public INetworkAccessManager
{
    Q_OBJECT
public:
    explicit NetworkAccessManager(QObject *parent = nullptr);
    ~NetworkAccessManager();

    QNetworkReply *get(const QNetworkRequest &request) override;
    QNetworkReply *post(const QNetworkRequest &request, const QByteArray &data) override;
    bool isNetAccessible() const override;

signals:

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

};

}}


#endif // NETWORKACCESSMANAGER_H
