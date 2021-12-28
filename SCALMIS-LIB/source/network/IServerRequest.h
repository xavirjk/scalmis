#ifndef ISERVERREQUEST_H
#define ISERVERREQUEST_H

#include <QObject>
#include <QUrl>
#include <SCALMIS-LIB_global.h>

namespace SCALMIS {
namespace network {

class SCALMISLIB_EXPORT IServerRequest: public QObject {
    Q_OBJECT
public:
    IServerRequest(QObject *parent = nullptr):
        QObject(parent){};
    virtual ~IServerRequest(){};

    virtual void executeGet(const QString &auth, const QString &ref) = 0;
    virtual void executeQuery(bool ref,const QString &text,const QString &auth) = 0;
    virtual void executePost(const QByteArray &data,const QString &user) = 0;
    virtual void executeSearch(const QString &text,const QString &searchkey) = 0;
    virtual bool isBusy() const = 0;
    virtual void fileHandling(bool status) const = 0;
    virtual void update(bool status) const = 0;
    virtual void setUrl( const QUrl &uri) = 0;
    virtual void setVersion(QString v) = 0;
    virtual QUrl uri() const = 0;

};

}
}
#endif // ISERVERREQUEST_H
