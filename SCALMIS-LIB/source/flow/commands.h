#ifndef COMMANDS_H
#define COMMANDS_H

#include <QObject>
#include "QScopedPointer"
#include <SCALMIS-LIB_global.h>
namespace SCALMIS {
namespace flow{

class SCALMISLIB_EXPORT  Commands : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_icon READ icon CONSTANT)
    Q_PROPERTY(QString ui_text READ text CONSTANT)
    Q_PROPERTY(bool ui_canExecute READ canExecute NOTIFY canExecuteChanged )
public:
    explicit Commands(QObject *parent = nullptr, const QString &icon = "",const QString &text = "" );
    ~Commands();

    const QString &icon() const;
    const QString &text() const;
    void reset();
    bool canExecute() const;

public slots:
    void execute();

signals:
    void executed();
    void canExecuteChanged();
private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

};

}
}


#endif // COMMANDS_H
