#ifndef REQUESTITEM_H
#define REQUESTITEM_H

#include <QObject>
#include <QJsonObject>
#include <SCALMIS-LIB_global.h>
#include <data/stringdecorator.h>
#include <data/intdecorator.h>
#include <data/entity.h>
using namespace SCALMIS::data;
namespace SCALMIS {
namespace models {
class SCALMISLIB_EXPORT RequestItem : public Entity
{
    Q_OBJECT

public:
    explicit RequestItem(QObject *parent = nullptr);
    RequestItem(QObject *parent, const QJsonObject &json);
    ~RequestItem();

    StringDecorator *item{nullptr};
    IntDecorator *totalValue{nullptr};

signals:

};
}}
#endif // REQUESTITEM_H
