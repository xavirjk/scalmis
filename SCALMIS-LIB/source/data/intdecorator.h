#ifndef INTDECORATOR_H
#define INTDECORATOR_H

#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QScopedPointer>

#include <SCALMIS-LIB_global.h>
#include <data/datadecorator.h>
#include <validators/validators.h>

namespace SCALMIS{
namespace data {

class SCALMISLIB_EXPORT IntDecorator : public DataDecorators
{
    Q_OBJECT

    Q_PROPERTY( int ui_input READ inputVal WRITE setVal NOTIFY valueChanged )

public:
    IntDecorator(Entity* parentEntity = nullptr, const QString& key = "SomeItemKey", const QString& label = "", int value = 0);
    ~IntDecorator();

    IntDecorator& setVal(int value);
    int inputVal() const;

public:
    QJsonValue jsonValue() const override;
    void update(const QJsonObject& jsonObject) override;

    bool inputValid() override;

signals:
    void valueChanged();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}}

#endif
