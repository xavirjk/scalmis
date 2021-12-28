#ifndef STOCK_H
#define STOCK_H

#include <QObject>
#include <QJsonObject>
#include <QtQml/QQmlListProperty>
#include <SCALMIS-LIB_global.h>
#include <data/entitycollection.h>
#include <data/entity.h>
#include <models/stockitem.h>
#include <models/service.h>
using namespace SCALMIS::data;
namespace SCALMIS {
namespace models {
class SCALMISLIB_EXPORT Stock : public Entity
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<SCALMIS::models::StockItem> ui_stock READ ui_stock NOTIFY stockChanged)
    Q_PROPERTY(QQmlListProperty<SCALMIS::models::Service> ui_service READ ui_service NOTIFY servicesChanged)
public:
    explicit Stock(QObject *parent = nullptr);
    Stock(QObject *parent, const QJsonObject &json);
    ~Stock();
    void clearStock();

    EntityCollection<StockItem > *stockItems{nullptr};
    EntityCollection<Service> *service{nullptr};
    QQmlListProperty<SCALMIS::models::StockItem> ui_stock();
    QQmlListProperty<SCALMIS::models::Service> ui_service();

public slots:
    void appendItem();
    void removeItem();
    void appendService();
    void removeService();
    void setmodels();
    void setServiceModel();

signals:
    void stockChanged();
    void servicesChanged();

};
}}
#endif // STOCK_H
