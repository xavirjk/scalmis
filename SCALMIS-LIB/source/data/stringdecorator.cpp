#include "stringdecorator.h"
#include <QVariant>

using namespace SCALMIS::validators;
namespace SCALMIS {
namespace data{

class StringDecorator::Implementation {
public:
    Implementation(StringDecorator *_stringDecorator, const QString &_value):
    stringDecorator(_stringDecorator),
    inputVal(_value)
    {}

    StringDecorator *stringDecorator{nullptr};
    Validators *validators{nullptr};
    QString inputVal;
};

StringDecorator::StringDecorator(Entity *parent, const QString &key, const QString &label, const QString &value) :
    DataDecorators(parent,key,label)
{
    implementation.reset(new Implementation(this, value));
    implementation->validators = new Validators(this,key);
}
StringDecorator::~StringDecorator(){}

const QString &StringDecorator::inputVal() const{
    return implementation->inputVal;
}

StringDecorator &StringDecorator::setVal(const QString &val){
    if(val!= implementation->inputVal){
        implementation->validators->validate(val);
        implementation->inputVal = val;
        emit inputChanged();
    }
    return *this;
}

QJsonValue StringDecorator::jsonValue() const{
    return QJsonValue::fromVariant(QVariant(implementation->inputVal));
}
void StringDecorator::update(const QJsonObject &payload){
    if(payload.contains(key())){
        setVal(payload.value(key()).toString());
    }
    else {
        setVal("");
    }

}

bool StringDecorator::inputValid(){
    return implementation->validators->validated();
}
}}
