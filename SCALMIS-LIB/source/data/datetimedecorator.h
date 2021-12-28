#ifndef DATETIMEDECORATOR_H
#define DATETIMEDECORATOR_H

#include <QDateTime>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QScopedPointer>

#include <SCALMIS-LIB_global.h>
#include <data/datadecorator.h>
#include <validators/validators.h>

namespace SCALMIS {
namespace data {

class SCALMISLIB_EXPORT DateTimeDecorator : public DataDecorators
{
    Q_OBJECT
    Q_PROPERTY( QString ui_iso8601String READ toIso8601String NOTIFY valueChanged )
    Q_PROPERTY( QString ui_prettyDateString READ toPrettyDateString NOTIFY valueChanged )
    //Q_PROPERTY( QString ui_prettyTimeString READ toPrettyTimeString NOTIFY valueChanged )
    Q_PROPERTY( QString ui_prettyString READ toPrettyString NOTIFY valueChanged )
    Q_PROPERTY( QDate ui_input READ inputVal WRITE setVal NOTIFY valueChanged )

public:
    DateTimeDecorator(Entity* parentEntity = nullptr, const QString& key = "SomeItemKey", const QString& label = "", const QDate &value = QDate::currentDate());
    ~DateTimeDecorator();

    const QDate& inputVal() const;
    DateTimeDecorator& setVal(const QDate& value);
    QString toIso8601String() const;
    QString toPrettyDateString() const;
    //QString toPrettyTimeString() const;
    QString toPrettyString() const;

    QJsonValue jsonValue() const override;
    void update(const QJsonObject& jsonObject) override;

    bool inputValid() override;

signals:
    void valueChanged();
    void StartAfresh();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}}
#endif // DATETIMEDECORATOR_H
