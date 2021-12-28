#include "networkaccessmanager.h"

namespace SCALMIS{
namespace network {

class NetworkAccessManager::Implementation {
public: Implementation()
    {}
    QNetworkAccessManager networkAccessManager;
};

NetworkAccessManager::NetworkAccessManager(QObject *parent) :
    INetworkAccessManager(parent)
{
    implementation.reset(new Implementation());

}

NetworkAccessManager::~NetworkAccessManager(){}

QNetworkReply *NetworkAccessManager::get(const QNetworkRequest &request){
    return implementation->networkAccessManager.get(request);
}

QNetworkReply *NetworkAccessManager::post(const QNetworkRequest &request, const QByteArray &data){
    return implementation->networkAccessManager.post(request, data);
}

bool NetworkAccessManager::isNetAccessible() const{
    return true;
}

}
}

