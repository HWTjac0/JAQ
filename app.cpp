#include "app.h"
#include <QQmlContext>
#include "core/apiclient.h"
#include "City/cityhandler.h"
#include "core/Database/database.h"
#include <QDir>

App::App() {}
int App::init(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ApiClient client;

    Database db(&client);
    CityHandler handler(&client);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("database", &db);
    engine.rootContext()->setContextProperty("cityHandler", &handler);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.addImportPath(QDir::currentPath() + "/Components");
    engine.loadFromModule("airQuality", "Main");
    return app.exec();
}
