#include "stationhandler.h"
#include "cityhandler.h"

Station StationHandler::currentStation;
StationHandler::StationHandler(ApiClient *apiClient, QObject *parent) : QObject(parent) {
    _stationModel = new StationModel(this);
    currentStation = Station();
    _apiClient = apiClient;
    _sensorHandler = new SensorHandler(this, apiClient);
}

void StationHandler::loadStationsForCity() {
    QList<Station> stations = CityHandler::currentCity->getStations();
    _stationModel->setStations(stations);
}

void StationHandler::stationSelected(int stationId) {
    currentStation = CityHandler::currentCity->getStationById(stationId);
    _sensorHandler->loadSensorsForStation();
    emit stationChanged();
}

StationModel* StationHandler::stationModel() const {
    return _stationModel;
}

SensorHandler* StationHandler::sensorHandler() {
    return _sensorHandler;
}

QString StationHandler::currentStationAddress() const {
    return currentStation.address();
}

int StationHandler::currentStationId() const {
    return currentStation.id();
}
