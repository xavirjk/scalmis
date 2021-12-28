#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QQmlContext>
#include <QIcon>
#include <controllers/mastercontroller.h>
#include <controllers/commandcontroller.h>
#include <controllers/navigationcontroller.h>
#include <flow/commands.h>
#include <data/stringdecorator.h>
#include <data/intdecorator.h>
#include <data/datetimedecorator.h>
#include <data/comboselect.h>
#include <data/comboselectdata.h>
#include <models/authlogin.h>
#include <models/stock.h>
#include <models/stockitem.h>
#include <models/service.h>
#include <models/requests.h>
#include <models/accounts.h>
#include <models/invoiceperiod.h>


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQuickWindow::setGraphicsApi(QSGRendererInterface::Software);

    qmlRegisterType<SCALMIS::controllers::MasterController>("SCALMIS", 1, 0,"MasterController");
    qmlRegisterType<SCALMIS::controllers::CommandController>("SCALMIS", 1, 0,"CommandController");
    qmlRegisterType<SCALMIS::controllers::NavigationController>("SCALMIS",1,0,"NavigationController");

    qmlRegisterType<SCALMIS::flow::Commands>("SCALMIS",1,0,"Commands");

    qmlRegisterType<SCALMIS::data::StringDecorator>("SCALMIS", 1, 0,"StringDecorator");
    qmlRegisterType<SCALMIS::data::IntDecorator>("SCALMIS",1,0,"IntDecorator");
    qmlRegisterType<SCALMIS::data::DateTimeDecorator>("SCALMIS",1,0,"DateTimeDecorator");
    qmlRegisterType<SCALMIS::data::ComboSelect>("SCALMIS",1,0,"ComboSelect");
    qmlRegisterType<SCALMIS::data::ComboSelectData>("SCALMIS",1,0,"ComboSelectData");

    qmlRegisterType<SCALMIS::models::AuthLogin>("SCALMIS", 1,0,"AuthLogin");
    qmlRegisterType<SCALMIS::models::Stock>("SCALMIS", 1, 0,"Stock");
    qmlRegisterType<SCALMIS::models::StockItem>("SCALMIS",1,0,"StockItem");
    qmlRegisterType<SCALMIS::models::Service>("SCALMIS", 1, 0,"Service");
    qmlRegisterType<SCALMIS::models::Requests>("SCALMIS",1,0,"Requests");
    qmlRegisterType<SCALMIS::models::Accounts>("SCALMIS",1,0,"Accounts");
    qmlRegisterType<SCALMIS::models::InvoicePeriod>("SCALMIS",1,0,"InvoicePeriod");
    SCALMIS::controllers::MasterController masterController;

    QQmlApplicationEngine engine;
    QObject::connect(&masterController, &SCALMIS::controllers::MasterController::killApp, QCoreApplication::quit);
    engine.addImportPath("qrc:/");
    engine.rootContext()->setContextProperty("masterController",&masterController);
    const QUrl url(QStringLiteral("qrc:/views/mainview.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
