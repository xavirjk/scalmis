#include "service.h"

namespace SCALMIS{
namespace models{
Service::Service(QObject *parent) : Entity(parent,"Service")
{
    service = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"item","Service")));
    amountAdded = static_cast<IntDecorator*>(addItem(new IntDecorator(this,"amountAdded","Number")));
    code = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"code","Service Code")));
    state = static_cast<IntDecorator*>(new IntDecorator(this,"state","state"));
}

Service::Service(QObject *parent, const QJsonObject &json):
    Service(parent){
    update(json);
}
Service::~Service(){}

}
}

