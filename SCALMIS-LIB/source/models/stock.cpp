#include "stock.h"
namespace SCALMIS {
namespace models {
Stock::Stock(QObject *parent) : Entity(parent,"Stock")
{
    stockItems = static_cast<EntityCollection<StockItem>*>(addChildCollection(new EntityCollection<StockItem>(this,"stockItems")));
    service = static_cast<EntityCollection<Service>*>(addChildCollection(new EntityCollection<Service>(this,"service")));
}
Stock::Stock(QObject *parent, const QJsonObject &json):Stock(parent){
    update(json);
}
void Stock::appendItem(){
    if(stockItems->derivedEntities().size() &&
            !(stockItems->derivedEntities().last()->item->inputValid() && stockItems->derivedEntities().last()->code->inputValid())) return;
    setmodels();
    stockItems->addEntity(new StockItem(this));
    emit stockChanged();
}
void Stock::setmodels(){
    for(int i = 0 ; i <stockItems->derivedEntities().size(); i++){
        stockItems->derivedEntities().at(i)->state->setVal(1);
    }
}
void Stock::setServiceModel(){
    for(int i = 0 ; i <service->derivedEntities().size(); i++){
        service->derivedEntities().at(i)->state->setVal(1);
    }
}
QQmlListProperty<StockItem> Stock::ui_stock(){
    return QQmlListProperty<StockItem>(this, &stockItems->derivedEntities());
}
QQmlListProperty<Service> Stock::ui_service(){
    return QQmlListProperty<Service>(this, &service->derivedEntities());
}
void Stock::removeItem(){
    stockItems->remove();
    if(stockItems->derivedEntities().size()) stockItems->derivedEntities().last()->state->setVal(0);
    emit stockChanged();
}
void Stock::appendService(){
    if(service->derivedEntities().size() &&
            !(service->derivedEntities().last()->service->inputValid() && service->derivedEntities().last()->code->inputValid())) return;
    setServiceModel();
    service->addEntity(new Service(this));
    emit servicesChanged();
}
void Stock::removeService(){
    service->remove();
    if(service->derivedEntities().size()) service->derivedEntities().last()->state->setVal(0);
    emit servicesChanged();
}
void Stock::clearStock(){
    int length = stockItems->derivedEntities().size();
    int len2 = service->derivedEntities().size();
    for(int i = 0 ; i < length; i++)stockItems->remove();
    for(int i = 0; i < len2; i++)service->remove();
    emit stockChanged();
    emit servicesChanged();
}
Stock::~Stock(){}


}}
