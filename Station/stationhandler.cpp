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
    qDebug() << "test";
}

StationModel* StationHandler::stationModel() const {
    return _stationModel;
}
