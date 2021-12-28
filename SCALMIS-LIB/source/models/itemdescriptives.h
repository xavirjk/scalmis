#ifndef ITEMDESCRIPTIVES_H
#define ITEMDESCRIPTIVES_H

#include <QObject>
#include <QJsonObject>
#include <SCALMIS-LIB_global.h>
#include <data/stringdecorator.h>
#include <data/intdecorator.h>
#include <data/entity.h>
using namespace SCALMIS::data;
namespace SCALMIS {
namespace models {
class SCALMISLIB_EXPORT ItemDescriptives : public Entity
{
    Q_OBJECT
public:
    explicit ItemDescriptives(QObject *parent = nullptr);
    ItemDescriptives(QObject *parent, const QJsonObject &json);
    ~ItemDescriptives();

    StringDecorator *description{nullptr};
    IntDecorator *progressCount{nullptr};

signals:

};
}}
#endif // ITEMDESCRIPTIVES_H
