#include "entity.h"
#include <QUuid>

namespace SCALMIS {
namespace data {
class Entity::Implementation {
public:Implementation(Entity *_entity, const QString &_key):
        entity(_entity),
        key(_key),
        id(QUuid::createUuid().toString().mid(1,36))
    {}
    Entity *entity{nullptr};
    const QString key = "";
    QString id = "";
    std::map<QString, EntityCollectionBase*>childCollections;
    std::map<QString, Entity*> childEntities;
    std::map<QString, DataDecorators*> dataDecorators;
};

Entity::Entity(QObject *parent, const QString &key) : QObject(parent)
{
    implementation.reset(new Implementation(this, key));
}

Entity::~Entity(){}

const QString &Entity::key() const{
    return implementation->key;
}

const QString &Entity::id() const{
    return implementation->id;
}

EntityCollectionBase* Entity::addChildCollection(EntityCollectionBase *entityCollection){
    if(implementation->childCollections.find(entityCollection->getKey()) == std::end(implementation->childCollections)){
        implementation->childCollections[entityCollection->getKey()] = entityCollection;
        emit childCollectionsChanged();
    }
    return entityCollection;
}

Entity *Entity::addChild(Entity *entity, const QString &key){
    if(implementation->childEntities.find(key) == std::end(implementation->childEntities)){
        implementation->childEntities[key] = entity;
        emit childEntitiesChanged();
    }
    return entity;
}

DataDecorators *Entity::addItem(DataDecorators *dataDecorator){
    if(implementation->dataDecorators.find(dataDecorator->key()) == std::end(implementation->dataDecorators)){
        implementation->dataDecorators[dataDecorator->key()] = dataDecorator;
        emit dataDecoratorsChanged();
    }
    return dataDecorator;
}

void Entity::update(const QJsonObject& payload){
    if(payload.contains("_id")){
        implementation->id = payload.value("_id").toString();
    }
    // Update data decorators
    for (std::pair<QString, DataDecorators*> dataDecoratorPair : implementation->dataDecorators) {

        dataDecoratorPair.second->update(payload);
    }

    // Update child entities
    for (std::pair<QString, Entity*> childEntityPair : implementation->childEntities) {
        childEntityPair.second->update(payload.value(childEntityPair.first).toObject());
    }

}

QJsonObject Entity::getCompleteJson(){
    QJsonObject json;
    for(std::pair<QString,DataDecorators*> dataDecoratorPair: implementation->dataDecorators){
        json.insert(dataDecoratorPair.first, dataDecoratorPair.second->jsonValue());
    }
    for(std::pair<QString, Entity*> childEntityPair: implementation->childEntities){
        json.insert(childEntityPair.first, childEntityPair.second->getCompleteJson());
    }
    for(std::pair<QString, EntityCollectionBase*> childCollectionPair: implementation->childCollections){
        QJsonArray entArray;
        for(Entity *entity: childCollectionPair.second->baseEntities()) {
            QJsonObject _json  = entity->getCompleteJson();
            entArray.append(_json);
        }
        json.insert(childCollectionPair.first,entArray);
    }
    return json;
}
}}

