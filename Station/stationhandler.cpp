#include "stationhandler.h"
#include "../core/Database/database.h"
#include "../City/cityhandler.h"

Station StationHandler::currentStation;
StationHandler::StationHandler(ApiClient *apiClient, QObject *parent) : QObject(parent) {
    _stationModel = new StationModel(this);
    currentStation = Station();
    _apiClient = apiClient;
}

void StationHandler::loadStationsForCity(int cityId) {
    QList<Station> stations = Database::getCity(cityId)->getStations();
    _stationModel->setStations(stations);
}

void StationHandler::stationSelected(int stationId) {
    currentStation = CityHandler::currentCity->getStationById(stationId);
    for(auto sensor : currentStation.getSensors()) {
        Indicator currentIndicator = Database::getIndicator(sensor.indicatorId());
        qDebug() << sensor.id() << " " << currentIndicator.name << " " << currentIndicator.code;
    }
}

StationModel* StationHandler::stationModel() const {
    return _stationModel;
}
