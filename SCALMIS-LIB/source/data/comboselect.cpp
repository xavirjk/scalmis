#include "comboselect.h"
namespace SCALMIS {
namespace data {

class ComboSelect::Implementation {
public:Implementation(ComboSelect *_comboselect, const std::map<QString,int> &_model):
        comboSelect(_comboselect)
    {
        for(auto &pair:_model){
            combo.append(new ComboSelectData(comboSelect,pair.first,pair.second));
        }
    }
    ComboSelect *comboSelect{nullptr};
    QList<ComboSelectData*> combo;
};

ComboSelect::ComboSelect(QObject *parent, const std::map<QString, int> &model) : QObject(parent)
{
    implementation.reset(new Implementation(this,model));

}

ComboSelect::~ComboSelect(){}

QQmlListProperty<ComboSelectData> ComboSelect::ui_combo(){
    return QQmlListProperty<ComboSelectData>(this,&implementation->combo);
}

}}

