#include "request.h"
namespace SCALMIS {
namespace models {
Request::Request(QObject *parent) : Entity(parent,"Request")
{
    //requestItems = static_cast<EntityCollection<RequestItem>*>(addChildCollection(new EntityCollection<RequestItem>(this,"requestItems")));
    //itemDescriptives = static_cast<EntityCollection<ItemDescriptives>*>(addChildCollection(new EntityCollection<ItemDescriptives>(this,"itemDescriptives")));
    //auths = static_cast<EntityCollection<Accounts>*>(addChildCollection(new EntityCollection<Accounts>(this,"Auths")));
    /*fullname = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"fullname","Officer")));
    office = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"office","Office")));*/
    quantity = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"quantity","Quantity")));
}
Request::Request(QObject *parent, const QJsonObject &json):
    Request(parent){
    update(json);
}
/*void Request::setupItemsModel(){
    for(int i = 0 ; i < requestItems->derivedEntities().size();i++){
        itemsModel.insert({requestItems->derivedEntities().at(i)->item->inputVal(),
                          requestItems->derivedEntities().at(i)->totalValue->inputVal()});
    }
    itemsComboSelect = new ComboSelect(this,itemsModel);   //Messy
    emit itemsComboChanged();
}
void Request::setUpDescModel(){
    descModel.clear();
    for(int i = 0 ; i < itemDescriptives->derivedEntities().size();i++){
        descModel.insert({itemDescriptives->derivedEntities().at(i)->description->inputVal(),
                          itemDescriptives->derivedEntities().at(i)->progressCount->inputVal()});
    }
    descComboSelect = new ComboSelect(this,descModel);   //Messy
    emit descComboChanged();
}
void Request::setUpAuthModel(){
    authsModel.insert({"Specify Other",0});
    for(int i = 0 ; i < auths->derivedEntities().size();i++){
        authsModel.insert({auths->derivedEntities().at(i)->office->inputVal(),
                          auths->derivedEntities().at(i)->pjno->inputVal()});
    }
    authsComboSelect = new ComboSelect(this,authsModel);   //Messy
    qDebug()<<"auths"<<authsModel;
    emit authsComboChanged();
}
QString Request::getItemId(const QString &item){
    for(int i = 0; i < requestItems->derivedEntities().size(); i++){
        if(requestItems->derivedEntities().at(i)->item->inputVal() == item)
            return requestItems->derivedEntities().at(i)->id();
    }
    return NULL;
}*/
Request::~Request(){}
}}
