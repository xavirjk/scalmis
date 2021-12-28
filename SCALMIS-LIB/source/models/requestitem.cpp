#include "requestitem.h"
namespace SCALMIS {
namespace models {
RequestItem::RequestItem(QObject *parent) : Entity(parent,"StockItem")
{
    item = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"item","Item")));
    totalValue = static_cast<IntDecorator*>(addItem(new IntDecorator(this,"totalValue","Total value")));
}
RequestItem::RequestItem(QObject *parent, const QJsonObject &json):
    RequestItem(parent){
    update(json);
}
RequestItem::~RequestItem(){}
}}
