#include "stockitem.h"

namespace SCALMIS{
namespace models{
StockItem::StockItem(QObject *parent) : Entity(parent,"StockItem")
{
    item = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"item","Item")));
    description = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"description","Item Description")));
    amountAdded = static_cast<IntDecorator*>(addItem(new IntDecorator(this,"amountAdded","Number")));
    code = static_cast<StringDecorator*>(addItem(new StringDecorator(this,"code","Item Code")));
    assetValue = static_cast<IntDecorator*>(addItem(new IntDecorator(this,"assetValue","Value")));
    dsamountAdded = static_cast<IntDecorator*>(addItem(new IntDecorator(this, "dsamountAdded", "Number")));
    dsassetValue = static_cast<IntDecorator*>(addItem(new IntDecorator(this,"dsassetValue","Value")));
    quantifier = static_cast<IntDecorator*>(addItem(new IntDecorator(this,"quantifier","quantifier")));
    pricing = static_cast<IntDecorator*>(addItem(new IntDecorator(this,"pricing","pricing")));
    state = static_cast<IntDecorator*>(new IntDecorator(this,"state","state"));
    quantifierModel = {
        {"Please select Quantifier",0},
        {"Piece",1},
        {"Pair", 2},
        {"Packet of 5",5},
        {"Packet of 10",10},
        {"dozen",12},
        {"Packet of 25", 25},
        {"Packet of 50", 50},
        {"Packet of 80",80},
        {"Packet of 100", 100},
        {"Packet of 240", 240},
        {"Packet of 500", 500},
        {"Packet of 1000", 1000}
    };
    pricingModel = {
        {"Quantifier Single pricing",0},
        {"Quantifier General pricing",1}
    };
    quantComboSelect = new ComboSelect(this,quantifierModel);
    pricingComboSelect = new ComboSelect(this,pricingModel);

    connect(dsassetValue,&IntDecorator::valueChanged,this,&StockItem::computeEntityValues);
    connect(dsamountAdded, &IntDecorator::valueChanged, this,&StockItem::computeEntityValues);
    connect(quantifier, &IntDecorator::valueChanged, this, &StockItem::computeEntityValues);
    connect(pricing, &IntDecorator::valueChanged,this,&StockItem::computeEntityValues);
}

StockItem::StockItem(QObject *parent, const QJsonObject &json):
    StockItem(parent){
    update(json);
}

QString StockItem::_id(){
    return "<b>Entry Id</b> : "+this->id();
}
void StockItem::computeEntityValues(){
    if(quantifier->inputVal()){
        if(pricing->inputVal())assetValue->setVal(dsassetValue->inputVal());
        else {
           assetValue->setVal(dsassetValue->inputVal() * dsamountAdded->inputVal());
           amountAdded->setVal(quantifier->inputVal()*dsamountAdded->inputVal());
        }
    }
    else {
        assetValue->setVal(dsassetValue->inputVal());
        amountAdded->setVal(dsamountAdded->inputVal());
    }
    emit computationValuesChanged();
}

const QString StockItem::getTotalAmount() const{
    return "Total Items: "+ QString::number(amountAdded->inputVal());
}
const QString StockItem::getTotalCost() const {
    return "Total cost: "+QString::number(assetValue->inputVal());
}
const QString StockItem::getFullItem() const{
    return description->inputVal() + " "+ item->inputVal();
}
StockItem::~StockItem(){}

}
}

