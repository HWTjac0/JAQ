#include "stationhandler.h"
#include "../core/Database/database.h"

StationHandler::StationHandler(ApiClient *apiClient, QObject *parent) : QObject(parent) {
    _stationModel = new StationModel(this);
    _currentStation = nullptr;
    _apiClient = apiClient;
}

void StationHandler::loadStationsForCity(int cityId) {
    QList<Station> stations = Database::getCity(cityId)->getStations();
    _stationModel->setStations(stations);
}

void StationHandler::getStationUrl(int stationId) {
    QUrl stationUrl = _apiClient->buildUrl("/aqindex/getIndex/" + QString::number(stationId));
    //_apiClient->fetchStationAQI(stationId);
    _apiClient->fetchSensors(stationId);
    qDebug() << stationUrl;
}

StationModel *StationHandler::stationModel() const {
    return _stationModel;
}
