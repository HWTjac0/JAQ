#include "app.h"
#include <QQmlContext>
#include <QApplication>
#include "core/apiclient.h"
#include "Handlers/cityhandler.h"
#include "core/Database/database.h"
#include <QDir>

#include "core/AppContext.h"

App::App() = default;
void App::initAppMetadata() {
    QCoreApplication::setApplicationName("Jacs Air Quality");
    QCoreApplication::setOrganizationName("hwtjac0");
    QCoreApplication::setApplicationVersion("2025.04");
}
int App::init(int argc, char *argv[])
{
    const QApplication app(argc, argv);

    AppContext& context = AppContext::getInstance();
    context.initialize();

    QStringList voivodeships = {"Dolnośląskie", "Kujawsko-pomorskie", "Lubelskie", "Lubuskie", "Łódzkie", "Małopolskie", "Mazowieckie", "Opolskie", "Podkarpackie", "Podlaskie", "Pomorskie", "Śląskie", "Świętokrzyskie", "Warmińsko-mazurskie", "Wielkopolskie", "Zachodniopomorskie"};

    initAppMetadata();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("voivodeshipsModel", voivodeships);
    engine.rootContext()->setContextProperty("appContext", &context);
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
