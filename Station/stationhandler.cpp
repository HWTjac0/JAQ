#include "stationhandler.h"
#include "../core/database.h"

StationHandler::StationHandler(QObject *parent) : QObject(parent) {
    _stationModel = new StationModel(this);
    _currentStation = nullptr;
}

void StationHandler::loadStationsForCity(int cityId) {
    QList<Station> stations = Database::getCity(cityId)->getStations();
    _stationModel->setStations(stations);
}

StationModel *StationHandler::stationModel() const {
    return _stationModel;
}
