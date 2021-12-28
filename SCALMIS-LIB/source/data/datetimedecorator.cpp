#include "datetimedecorator.h"
#include <QVariant>

using namespace SCALMIS::validators;
namespace SCALMIS {
namespace data {

class DateTimeDecorator::Implementation
{
public:
    Implementation(DateTimeDecorator* dateTimeDecorator, const QDate& value)
        : dateTimeDecorator(dateTimeDecorator)
        , value(value)
    {
    }

    DateTimeDecorator* dateTimeDecorator{nullptr};
    Validators *validators{nullptr};
    QDate value;
};

DateTimeDecorator::DateTimeDecorator(Entity* parentEntity, const QString& key, const QString& label, const QDate& value)
    : DataDecorators(parentEntity, key, label)
{
    implementation.reset(new Implementation(this, value));
    implementation->validators = new Validators(this,key);
}

DateTimeDecorator::~DateTimeDecorator()
{
}

const QDate& DateTimeDecorator::inputVal() const
{
    return implementation->value;
}

bool DateTimeDecorator::inputValid(){
    return implementation->validators->validated();
}

DateTimeDecorator& DateTimeDecorator::setVal(const QDate& value)
{
    if(value != implementation->value){
        // ...Validation here if required...
        implementation->value = value;
        emit valueChanged();
    }
    return *this;
}

QString DateTimeDecorator::toIso8601String() const
{
    if (implementation->value.isNull()) {
        return "";
    } else {
        return implementation->value.toString(Qt::ISODate);
    }
}

QString DateTimeDecorator::toPrettyString() const
{
    if (implementation->value.isNull()) {
        return "Not set";
    } else {
        return implementation->value.toString( "ddd d MMM yyyy @ HH:mm:ss" );
    }
}

QString DateTimeDecorator::toPrettyDateString() const
{
    if (implementation->value.isNull()) {
        return "Not set";
    } else {
        return implementation->value.toString( "d MMM yyyy" );
    }
}

QJsonValue DateTimeDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(implementation->value.toString(Qt::ISODate)));
}

void DateTimeDecorator::update(const QJsonObject& jsonObject)
{
    if (jsonObject.contains(key())) {
        auto valueAsString = jsonObject.value(key()).toString();
        auto valueAsDate = QDate::fromString(valueAsString, Qt::ISODate);  // yyyy-MM-ddTHH:mm:ss
        setVal(valueAsDate);
    } else {
        setVal(QDate());
    }
}

}}
