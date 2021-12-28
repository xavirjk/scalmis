#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <QObject>
#include <QScopedPointer>
#include <SCALMIS-LIB_global.h>
#include <QRegularExpression>
namespace SCALMIS {
namespace validators {

class SCALMISLIB_EXPORT Validators : public QObject
{
    Q_OBJECT
public:
    explicit Validators(QObject *parent = nullptr, const QString key = "");
    ~Validators();

    void validate(const QString &data = "");

    bool validated();

    class Implementation;
    QScopedPointer<Implementation> implementation;

signals:

};

}}


#endif // VALIDATORS_H
