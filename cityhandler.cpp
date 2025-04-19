#include "cityhandler.h"
#include <QStringList>
#include "database.h"

CityHandler::CityHandler(ApiClient *client)
    : _client(client)
{}

void CityHandler::receiveText(const QString &text)
{
    qDebug() << "Received text from QML:" << text;
    Database::index.value(text).debugStations();
}

QStringList CityHandler::getCities() const {
    return Database::cities;
}
