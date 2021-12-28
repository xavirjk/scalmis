#ifndef INETWORKACCESSMANAGER_H
#define INETWORKACCESSMANAGER_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>


#include "SCALMIS-LIB_global.h"



namespace SCALMIS{
namespace network {

class SCALMISLIB_EXPORT INetworkAccessManager: public QObject{
    Q_OBJECT
public:
    INetworkAccessManager(QObject *parent = nullptr):
        QObject(parent){};
    virtual ~INetworkAccessManager(){}

    virtual QNetworkReply *get(const QNetworkRequest &request) = 0;
    virtual QNetworkReply *post(const QNetworkRequest &request, const QByteArray &data) = 0;
    virtual bool isNetAccessible() const = 0;

signals:

};

}
}


#endif // INETWORKACCESSMANAGER_H
