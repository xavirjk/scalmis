#ifndef INVOICEPERIOD_H
#define INVOICEPERIOD_H
#include <SCALMIS-LIB_global.h>
#include <QObject>
#include "data/entity.h"
#include "data/datadecorator.h"
#include "data/datetimedecorator.h"
using namespace SCALMIS::data;
namespace SCALMIS {
namespace models {
class SCALMISLIB_EXPORT InvoicePeriod : public Entity
{
    Q_OBJECT
    Q_PROPERTY(SCALMIS::data::DateTimeDecorator *ui_from MEMBER from CONSTANT)
    Q_PROPERTY(SCALMIS::data::DateTimeDecorator *ui_to MEMBER to CONSTANT)
public:
    explicit InvoicePeriod(QObject *parent = nullptr);
    InvoicePeriod(QObject *parent, const QJsonObject &json);
    ~InvoicePeriod();

    DateTimeDecorator *from{nullptr};
    DateTimeDecorator *to{nullptr};

signals:

};
}}

#endif // INVOICEPERIOD_H
