#include "requests.h"
namespace SCALMIS {
namespace models {
Requests::Requests(QObject *parent) : Entity(parent,"entry")
{
    officer = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"officer","Officer Identity")));
    office = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"office","Office")));
    toggle = static_cast<IntDecorator*>(new IntDecorator(this,"toggle","Toggle"));
    requestItems = static_cast<EntityCollection<RequestItem>*>(addChildCollection(new EntityCollection<RequestItem>(this,"requestItems")));
    itemDescriptives = static_cast<EntityCollection<ItemDescriptives>*>(addChildCollection(new EntityCollection<ItemDescriptives>(this,"itemDescriptives")));
    requestServices = static_cast<EntityCollection<Service>*>(addChildCollection(new EntityCollection<Service>(this,"requestService")));
    auths = static_cast<EntityCollection<Accounts>*>(addChildCollection(new EntityCollection<Accounts>(this,"Auths")));
    requests = static_cast<EntityCollection<StockItem>*>(addChildCollection(new EntityCollection<StockItem>(this,"Requests")));
    srvrequests = static_cast<EntityCollection<Service>*>(addChildCollection(new EntityCollection<Service>(this,"SrvRequests")));

    connect(toggle,&IntDecorator::valueChanged,this,&Requests::toggleChanged);
}
Requests::Requests(QObject *parent, const QJsonObject &json):
    Requests(parent){
    update(json);
}
void Requests::emitToggled(){
    emit toggleChanged();
}
void Requests::setupItemsModel(){
    itemsModel.clear();
    for(int i = 0; i <requestItems->derivedEntities().size() ; i++){
        itemsModel.insert({requestItems->derivedEntities().at(i)->item->inputVal(),
                          requestItems->derivedEntities().at(i)->totalValue->inputVal()});
    }
    itemsComboSelect = new ComboSelect(this,itemsModel);   //Messy
    emit itemsComboChanged();
}
void Requests::setUpDescModel(){
    descModel.clear();
    for(int i = 0 ; i < itemDescriptives->derivedEntities().size();i++){
        descModel.insert({itemDescriptives->derivedEntities().at(i)->description->inputVal(),
                          itemDescriptives->derivedEntities().at(i)->progressCount->inputVal()});
    }
    descComboSelect = new ComboSelect(this,descModel);   //Messy
    emit descComboChanged();
}
void Requests::setUpAuthModel(){
    for(int i = 0 ; i < auths->derivedEntities().size();i++){;
        authsModel.insert({auths->derivedEntities().at(i)->office->inputVal(),i+1});
    }
    authsComboSelect = new ComboSelect(this,authsModel);   //Messy
    emit authsComboChanged();
}
void Requests::setUpServicesModel(){
    servicesModel.clear();
    for(int i = 0 ; i < requestServices->derivedEntities().size();i++){
        servicesModel.insert({requestServices->derivedEntities().at(i)->service->inputVal(),i});
    }
    srvComboSelect = new ComboSelect(this,servicesModel);   //Messy
    emit srvComboChanged();
}
QString Requests::getItemId(const QString &item){
    for(int i = 0; i < requestItems->derivedEntities().size(); i++){
        if(requestItems->derivedEntities().at(i)->item->inputVal() == item)
            return requestItems->derivedEntities().at(i)->id();
    }
    return NULL;
}
QString Requests::getServiceId(const QString &service){
    for(int i = 0; i < requestServices->derivedEntities().size(); i++){
        if(requestServices->derivedEntities().at(i)->service->inputVal() == service)
            return requestServices->derivedEntities().at(i)->id();
    }
    return NULL;
}
void Requests::appendService(){
    if(srvrequests->derivedEntities().size() &&
            !(srvrequests->derivedEntities().last()->service->inputValid())) return;
    setServiceModels();
    srvrequests->addEntity(new Service(this));
    emit srvRequestsChanged();
}
void Requests::removeService(){
    srvrequests->remove();
    if(srvrequests->derivedEntities().size()) srvrequests->derivedEntities().last()->state->setVal(0);
    emit srvRequestsChanged();
}
void Requests::appendItem(){
    if(requests->derivedEntities().size() &&
            !(requests->derivedEntities().last()->item->inputValid())) return;
    setmodels();
    requests->addEntity(new StockItem(this));
    emit requestsChanged();
}

void Requests::setServiceModels(){
    for(int i = 0 ; i <srvrequests->derivedEntities().size(); i++){
        srvrequests->derivedEntities().at(i)->state->setVal(1);
    }
}
void Requests::setmodels(){
    for(int i = 0 ; i <requests->derivedEntities().size(); i++){
        requests->derivedEntities().at(i)->state->setVal(1);
    }
}
void Requests::removeItem(){
    requests->remove();
    if(requests->derivedEntities().size()) requests->derivedEntities().last()->state->setVal(0);
    emit requestsChanged();
}
void Requests::clearRequests(){
    QJsonArray empty;
    officer->setVal("");
    office->setVal("");
    requestItems->update(empty);
    itemDescriptives->update(empty);
    auths->update(empty);
    requests->update(empty);
    srvrequests->update(empty);
    emit requestsChanged();
    emit srvRequestsChanged();
}
void Requests::officeMembers(){
    members.clear();
    for( int i = 0; i < auths->derivedEntities().size(); i++){
        if(auths->derivedEntities().at(i)->office->inputVal() == office->inputVal()){
            members.insert({auths->derivedEntities().at(i)->fullname->inputVal(),
                           auths->derivedEntities().at(i)->pjno->inputVal()});
        }
    }
    if(members.size() == 1)
        officer->setVal(QString::number(members.begin()->second));
    membersComboSelect = new ComboSelect(this, members);
    emit membersComboChanged();
}
QQmlListProperty<StockItem> Requests::ui_requests(){
    return QQmlListProperty<StockItem>(this, &requests->derivedEntities());
}
QQmlListProperty<Service> Requests::ui_srvrequests(){
    return QQmlListProperty<Service>(this, &srvrequests->derivedEntities());
}
Requests::~Requests(){}
}}
