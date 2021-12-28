#ifndef COMBOSELECTDATA_H
#define COMBOSELECTDATA_H

#include <QObject>
#include <QScopedPointer>
#include "SCALMIS-LIB_global.h"

namespace SCALMIS {
namespace data {

class SCALMISLIB_EXPORT ComboSelectData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_key READ key CONSTANT)
    Q_PROPERTY(int ui_value READ value CONSTANT)
public:
    explicit ComboSelectData(QObject *parent = nullptr,const QString &key = "", const int &value = 0);
    ~ComboSelectData();

    QString &key() const;
    int &value() const;

signals:

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

};

}
}

#endif // COMBOSELECTDATA_H
