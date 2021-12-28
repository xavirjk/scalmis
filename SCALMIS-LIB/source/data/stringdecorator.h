#ifndef STRINGDECORATOR_H
#define STRINGDECORATOR_H

#include <QObject>
#include <QString>
#include <QJsonValue>
#include <QJsonObject>
#include <QScopedPointer>
#include <SCALMIS-LIB_global.h>
#include "data/datadecorator.h"
#include "validators/validators.h"

namespace SCALMIS {
namespace data {
class SCALMISLIB_EXPORT StringDecorator : public DataDecorators
{
    Q_OBJECT
    Q_PROPERTY(QString ui_input READ inputVal WRITE setVal NOTIFY inputChanged)
public:
    explicit StringDecorator(Entity *parentEntity = nullptr,const QString &key = "itemKey", const QString &label = "", const QString &value = "");
    ~StringDecorator();

    const QString &inputVal() const;
    StringDecorator &setVal(const QString &val);

    QJsonValue jsonValue() const override;
    void update(const QJsonObject &payload) override;

    bool inputValid() override;

signals:
    void inputChanged();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}}

#endif // STRINGDECORATOR_H

