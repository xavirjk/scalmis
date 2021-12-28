#include "invoiceperiod.h"
namespace SCALMIS {
namespace models {

InvoicePeriod::InvoicePeriod(QObject *parent) : Entity(parent,"period")
{
    from = static_cast<DateTimeDecorator*>(addItem(new DateTimeDecorator(this,"from","From")));
    to = static_cast<DateTimeDecorator*>(addItem(new DateTimeDecorator(this,"to","To")));

}
InvoicePeriod::InvoicePeriod(QObject *parent, const QJsonObject &json):
    InvoicePeriod(parent){
    update(json);
}
InvoicePeriod::~InvoicePeriod(){}

}}
