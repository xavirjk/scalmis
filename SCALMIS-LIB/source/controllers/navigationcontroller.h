#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H
#include <QObject>
#include <SCALMIS-LIB_global.h>
#include <QJsonArray>
namespace SCALMIS {
namespace controllers {
class SCALMISLIB_EXPORT NavigationController: public QObject {
    Q_OBJECT
public:
    NavigationController(QObject *parent = nullptr):
        QObject(parent){}
    ~NavigationController(){}
signals:
    void goLogoutAdmin();
    void goAdminView();
    void goAdminDashboardView();
    void goHomeView();
    void goCreateUserView();
    void goEditUserView();
    void goCreateNewStockTake();
    void goRequestItem();
    void goSelectItems();
    void goSelectServices();
    void goIssueItems();
    void goViewStock(QJsonArray json);
    void goViewItems(QJsonArray json);
    void goCreateNewUser();
    void goViewIssuedItems(QJsonArray json);
    void goViewStockItems(const QString &type);
    void goGetDates();
    void goRenderUsers(QJsonArray body);
    void goCheckUpdates();
};

}

}

#endif // NAVIGATIONCONTROLLER_H
