#include "commands.h"
using namespace SCALMIS::flow;
class Commands::Implementation {
public:Implementation(Commands *_commands, const QString &_icon = "", const QString &_text = ""):
        commands(_commands), icon(_icon),text(_text)
    {}
    Commands *commands{nullptr};
    QString icon;
    QString text;
    bool canExecute = true;
};

Commands::Commands(QObject *parent, const QString &icon, const QString &text) : QObject(parent)
{
    implementation.reset(new Implementation(this,icon,text));
}

const QString &Commands::icon() const{
    return implementation->icon;
}

const QString &Commands::text() const{
    return implementation->text;
}
void Commands::reset(){
    implementation->canExecute = true;
    emit canExecuteChanged();
}
void Commands::execute(){
    implementation->canExecute = false;
    emit canExecuteChanged();
    emit executed();
}
bool Commands::canExecute() const{
    return implementation->canExecute;
}
Commands::~Commands(){}
