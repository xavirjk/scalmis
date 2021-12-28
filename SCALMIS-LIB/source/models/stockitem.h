#ifndef STOCKITEM_H
#define STOCKITEM_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <SCALMIS-LIB_global.h>
#include <data/stringdecorator.h>
#include <data/intdecorator.h>
#include <data/entity.h>
#include <data/comboselect.h>
using namespace SCALMIS::data;
namespace SCALMIS {
namespace models {

class SCALMISLIB_EXPORT StockItem : public Entity
{
    Q_OBJECT
    Q_PROPERTY(SCALMIS::data::StringDecorator *ui_item MEMBER item CONSTANT)
    Q_PROPERTY(SCALMIS::data::StringDecorator *ui_description MEMBER description CONSTANT)
    Q_PROPERTY(SCALMIS::data::StringDecorator *ui_code MEMBER code CONSTANT)
    Q_PROPERTY(SCALMIS::data::IntDecorator *ui_amountAdded MEMBER dsamountAdded CONSTANT)
    Q_PROPERTY(SCALMIS::data::IntDecorator *ui_assetValue MEMBER dsassetValue CONSTANT)
    Q_PROPERTY(SCALMIS::data::ComboSelect* ui_quantComboSelect MEMBER quantComboSelect CONSTANT)
    Q_PROPERTY(SCALMIS::data::ComboSelect* ui_pricingComboSelect MEMBER pricingComboSelect CONSTANT)
    Q_PROPERTY(SCALMIS::data::IntDecorator *ui_quantifier MEMBER quantifier CONSTANT)
    Q_PROPERTY(SCALMIS::data::IntDecorator *ui_pricing MEMBER pricing CONSTANT)
    Q_PROPERTY(SCALMIS::data::IntDecorator *ui_state MEMBER state CONSTANT)
    Q_PROPERTY(QString ui_totalCost READ getTotalCost NOTIFY computationValuesChanged)
    Q_PROPERTY(QString ui_totalAmount READ getTotalAmount NOTIFY computationValuesChanged)
    Q_PROPERTY(QString ui_fullItem READ getFullItem CONSTANT)
    Q_PROPERTY(QString ui_id READ _id CONSTANT)
public:
    explicit StockItem(QObject *parent = nullptr);
    StockItem(QObject *parent, const QJsonObject &json);
    ~StockItem();

    ComboSelect *quantComboSelect{nullptr};
    ComboSelect *pricingComboSelect{nullptr};
    StringDecorator *item{nullptr};
    StringDecorator *description{nullptr};
    StringDecorator *code{nullptr};
    IntDecorator *amountAdded{nullptr};
    IntDecorator *assetValue{nullptr};
    IntDecorator *dsamountAdded{nullptr};
    IntDecorator *dsassetValue{nullptr};
    IntDecorator *quantifier{nullptr};
    IntDecorator *pricing{nullptr};
    IntDecorator *state{nullptr};

    QString _id();
    const QString getTotalCost() const;
    const QString getTotalAmount() const;
    const QString getFullItem() const;

public slots:
    void computeEntityValues();
signals:
    void computationValuesChanged();
private:
    std::map<QString,int> quantifierModel;
    std::map<QString,int> pricingModel;
};
}}

#endif // STOCKITEM_H
