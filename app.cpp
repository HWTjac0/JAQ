#include "app.h"
#include <QQmlContext>
#include "apiclient.h"
#include "City/cityhandler.h"
#include "database.h"
#include <QDir>

App::App() {}
int App::init(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ApiClient client;

    Database db(&client);
    CityHandler handler(&client);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("cityHandler", &handler);
    engine.
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
