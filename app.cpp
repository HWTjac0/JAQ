#include "app.h"
#include "apiclient.h"
#include "cityhandler.h"
#include <QQmlContext>

App::App() {}
int App::init(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    ApiClient client;

    CityHandler handler(&client);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("cityHandler", &handler);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("airQuality", "Main");

    return app.exec();
}
