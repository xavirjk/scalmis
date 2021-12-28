#include "datadecorator.h"
namespace SCALMIS {
namespace data {
class DataDecorators::Implementation{
public:Implementation(Entity *_parent, const QString &_key, const QString &_label):
    parentEntity(_parent),
      label(_label),
      key(_key)

    {}

    Entity *parentEntity{nullptr};
    QString label;
    QString key;
};

DataDecorators::DataDecorators(Entity *parent, const QString &key, const QString &label) :
    QObject((QObject*)parent)
{
    implementation.reset(new Implementation(parent,key,label));

}
DataDecorators::~DataDecorators(){}

const QString &DataDecorators::inputLabel() const{
    return implementation->label;
}

void DataDecorators::setLabel(const QString &label){
    if(implementation->label == label){
        return;
    }
    implementation->label = label;
    emit labelChanged();
}

const QString &DataDecorators::key() const{
    return implementation->key;
}

Entity *DataDecorators::parentEntity(){
    return implementation ->parentEntity;
}

}}

