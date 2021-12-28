#include "comboselectdata.h"
namespace SCALMIS {
namespace data {

class ComboSelectData::Implementation {
public:Implementation(ComboSelectData *_comboSelectData, const QString &_key, const int&_value):
        comboSelectData(_comboSelectData),
        key(_key),
        value(_value)
    {

    }
    ComboSelectData *comboSelectData{nullptr};
    QString key;
    int value;
};

ComboSelectData::ComboSelectData(QObject *parent, const QString &key, const int &value) : QObject(parent)
{
    implementation.reset(new Implementation(this,key,value));
}

ComboSelectData::~ComboSelectData(){}

QString &ComboSelectData::key() const{
    return implementation->key;
}

int &ComboSelectData::value() const{
    return implementation->value;
}

}}
