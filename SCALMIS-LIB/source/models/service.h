#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <SCALMIS-LIB_global.h>
#include <data/stringdecorator.h>
#include <data/intdecorator.h>
#include <data/entity.h>
using namespace SCALMIS::data;
namespace SCALMIS {
namespace models {

class SCALMISLIB_EXPORT Service : public Entity
{
    Q_OBJECT
    Q_PROPERTY(SCALMIS::data::StringDecorator *ui_service MEMBER service CONSTANT)
    Q_PROPERTY(SCALMIS::data::StringDecorator *ui_code MEMBER code CONSTANT)
    Q_PROPERTY(SCALMIS::data::IntDecorator *ui_amountAdded MEMBER amountAdded CONSTANT)
    Q_PROPERTY(SCALMIS::data::IntDecorator *ui_state MEMBER state CONSTANT)
public:
    explicit Service(QObject *parent = nullptr);
    Service(QObject *parent, const QJsonObject &json);
    ~Service();

    StringDecorator *service{nullptr};
    StringDecorator *code{nullptr};
    IntDecorator *amountAdded{nullptr};
    IntDecorator *state{nullptr};
};
}}

#endif // SERVICE_H
