#include "app.h"
#include <QQmlContext>
#include <QApplication>
#include "core/apiclient.h"
#include "Handlers/cityhandler.h"
#include "core/Database/database.h"
#include <QDir>

#include "core/AppContext.h"
App* App::_instance;
App::App() = default;

App * App::instance() {
    if (_instance == nullptr) {
        _instance = new App();
    }
    return _instance;
}

void App::initAppMetadata() {
    QCoreApplication::setApplicationName("Jacs Air Quality");
    QCoreApplication::setOrganizationName("hwtjac0");
    QCoreApplication::setApplicationVersion("2025.04");
}
int App::init(int argc, char *argv[])
{
    const QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.addImportPath(QDir::currentPath() + "/Components");

    AppContext* context = AppContext::getInstance();
    QStringList voivodeships = {"Dolnośląskie", "Kujawsko-pomorskie", "Lubelskie", "Lubuskie", "Łódzkie", "Małopolskie", "Mazowieckie", "Opolskie", "Podkarpackie", "Podlaskie", "Pomorskie", "Śląskie", "Świętokrzyskie", "Warmińsko-mazurskie", "Wielkopolskie", "Zachodniopomorskie"};

    connect(context, &AppContext::initialized, this, [&engine, voivodeships, context]() {
            qDebug() << "App initialized";
            engine.rootContext()->setContextProperty("appContext", context);
            engine.loadFromModule("airQuality", "Main");
        });
    context->initialize();

    initAppMetadata();

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);


    return app.exec();
}
