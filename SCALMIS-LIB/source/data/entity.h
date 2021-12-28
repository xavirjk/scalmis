#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QString>

#include <map>
#include <QJsonObject>
#include <QJsonArray>

#include <QScopedPointer>
#include <SCALMIS-LIB_global.h>
#include <data/datadecorator.h>
#include <data/entitycollection.h>
namespace SCALMIS {
namespace data {

class SCALMISLIB_EXPORT Entity : public QObject
{
    Q_OBJECT
public:
    explicit Entity(QObject *parent = nullptr,const QString &key = "item Key");
    ~Entity();
    const QString &key() const;
    const QString &id() const;
    void update(const QJsonObject &payload);
    QJsonObject getCompleteJson();
signals:
    void childCollectionsChanged();
    void childEntitiesChanged();
    void dataDecoratorsChanged();

protected:
    EntityCollectionBase* addChildCollection(EntityCollectionBase* entityCollection);
    Entity *addChild(Entity *entity, const QString &key = "");
    DataDecorators *addItem(DataDecorators *dataDecorator);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}}


#endif // ENTITY_H
