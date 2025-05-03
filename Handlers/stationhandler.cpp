#include "stationhandler.h"
#include "cityhandler.h"
#include "core/AppContext.h"

Station StationHandler::currentStation;
StationHandler::StationHandler(ApiClient* apiClient, SensorHandler* sensorHandler, QObject *parent) : QObject(parent) {
    _stationModel = new StationModel(this);
    currentStation = Station();
    _apiClient = apiClient;
    _sensorHandler = sensorHandler;

    // SIGNAL HANDLERS
    connect(_apiClient, &ApiClient::stationAQIFinished, this, &StationHandler::processAQI);
}

void StationHandler::loadStationsForCity() {
    QList<Station> stations = CityHandler::currentCity->getStations();
    _stationModel->setStations(stations);
}

void StationHandler::stationSelected(int stationId) {
    currentStation = CityHandler::currentCity->getStationById(stationId);
    _sensorHandler->loadSensorsForStation();
    emit stationChanged();
    _apiClient->fetchStationAQI(currentStationId());
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

QGeoCoordinate StationHandler::currentStationCoordinate() const {
    QGeoCoordinate stationCoords(currentStation.getCoords().x, currentStation.getCoords().y);
    return stationCoords;
}

int StationHandler::currentStationId() const {
    return currentStation.id();
}

void StationHandler::processAQI(QJsonDocument aqiDoc) {
    QJsonObject aqiRoot = aqiDoc.object().value("AqIndex").toObject();
    QString aqiStatus = aqiRoot.value("Nazwa kategorii indeksu").toString();
    emit stationAQIAcquired(aqiStatus);
}
