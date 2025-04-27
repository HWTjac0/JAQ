#include "app.h"
#include <QQmlContext>
#include "core/apiclient.h"
#include "Handlers/cityhandler.h"
#include "core/Database/database.h"
#include <QDir>
#include <QStringList>

App::App() {}
int App::init(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ApiClient client;

    Database db(&client);
    CityHandler cityHandler(&client);
    StationHandler *stationHandler = cityHandler.stationHandler();
    SensorHandler *sensorHandler = stationHandler->sensorHandler();

    QStringList voivodeships = {"Dolnośląskie", "Kujawsko-pomorskie", "Lubelskie", "Lubuskie", "Łódzkie", "Małopolskie", "Mazowieckie", "Opolskie", "Podkarpackie", "Podlaskie", "Pomorskie", "Śląskie", "Świętokrzyskie", "Warmińsko-mazurskie", "Wielkopolskie", "Zachodniopomorskie"};

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("voivodeshipsModel", voivodeships);
    engine.rootContext()->setContextProperty("stationHandler", stationHandler);
    engine.rootContext()->setContextProperty("sensorHandler", sensorHandler);
    engine.rootContext()->setContextProperty("cityHandler", &cityHandler);
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
