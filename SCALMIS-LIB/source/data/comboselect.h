#ifndef COMBOSELECT_H
#define COMBOSELECT_H

#include <QObject>
#include <map>
#include <QtQml/QQmlListProperty>
#include "QScopedPointer"
#include "SCALMIS-LIB_global.h"
#include "data/comboselectdata.h"


namespace SCALMIS {
namespace data {

class  SCALMISLIB_EXPORT ComboSelect : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<ComboSelectData> ui_combo READ ui_combo CONSTANT)

public:
    explicit ComboSelect(QObject *parent = nullptr, const std::map<QString,int> &model = std::map<QString,int>());
    ~ComboSelect();

    QQmlListProperty<ComboSelectData> ui_combo();


signals:

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};


}}


#endif // COMBOSELECT_H
