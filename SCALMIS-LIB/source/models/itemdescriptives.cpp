#include "itemdescriptives.h"
namespace SCALMIS {
namespace models {
ItemDescriptives::ItemDescriptives(QObject *parent) : Entity(parent)
{
    description = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"description","Description")));
    progressCount = static_cast<IntDecorator*>(addItem(new IntDecorator(this,"progressCount","Progress Count")));
}
ItemDescriptives::ItemDescriptives(QObject *parent, const QJsonObject &json):
    ItemDescriptives(parent){
    update(json);
}
ItemDescriptives::~ItemDescriptives(){}
}}
