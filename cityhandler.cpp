#include "cityhandler.h"

CityHandler::CityHandler(ApiClient* client) : _client(client) {}

void CityHandler::receiveText(const QString &text) {
    qDebug() << "Received text from QML:" << text;
    _client->fetchStations();
}
