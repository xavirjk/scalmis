#include "intdecorator.h"

#include <QVariant>
using namespace SCALMIS::validators;

namespace SCALMIS {
namespace data {

class IntDecorator::Implementation
{
public:
    Implementation(IntDecorator* intDecorator, int value)
        : intDecorator(intDecorator)
        , value(value)
    {
    }

    IntDecorator* intDecorator{nullptr};
    Validators *validators{nullptr};
    int value;
};

IntDecorator::IntDecorator(Entity* parentEntity, const QString& key, const QString& label, int value)
    : DataDecorators(parentEntity, key, label)
{
    implementation.reset(new Implementation(this, value));
    implementation->validators = new Validators(this,key);
}

IntDecorator::~IntDecorator()
{
}

int IntDecorator::inputVal() const
{
    return implementation->value;
}

IntDecorator& IntDecorator::setVal(int value)
{
    if(value != implementation->value) {
        // ...Validation here if required...
        implementation->value = value;
        emit valueChanged();
    }
    else emit valueChanged();
    return *this;
}

QJsonValue IntDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(implementation->value));
}

void IntDecorator::update(const QJsonObject& jsonObject)
{
    if (jsonObject.contains(key())) {
        auto l_value = jsonObject.value(key()).toInt();
        setVal(l_value);
    } else {
        setVal(0);
    }
}

bool IntDecorator::inputValid(){
    return implementation->validators->validated();
}

}}
