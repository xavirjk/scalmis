#ifndef DATADECORATORS_H
#define DATADECORATORS_H

#include <QObject>
#include <QJsonValue>
#include <QScopedPointer>
#include <SCALMIS-LIB_global.h>

namespace SCALMIS {
namespace data {

class Entity;

class SCALMISLIB_EXPORT DataDecorators : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_label READ inputLabel WRITE setLabel NOTIFY labelChanged)
public:
    DataDecorators(Entity *parent = nullptr,const QString &key = "key", const QString &label = "label");
    ~DataDecorators();
    const QString &inputLabel() const;
    void setLabel(const QString &label);
    const QString &key() const;
    Entity *parentEntity();

    virtual QJsonValue jsonValue() const = 0;
    virtual void update(const QJsonObject& payload) = 0;
    virtual bool inputValid()  = 0;
signals:
    void labelChanged();
private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}}


#endif // DATADECORATORS_H
