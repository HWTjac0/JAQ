#include "cityhandler.h"
#include "../Models/citysortproxymodel.h"
#include <QStringList>
#include "../core/Database/database.h"
#include "core/AppContext.h"
#include "Entities/station.h"

City *CityHandler::currentCity = nullptr;

CityHandler::CityHandler(ApiClient* apiClient, StationHandler* stationHandler, QObject *parent)
    : QObject(parent)
{
    _client = apiClient;
    _geoLocator = new GeoLocator(this);
    _stationHandler = stationHandler;

    _stationMarkers = new StationCoordinateModel(this);
    _baseModel = new CityIndexModel(this);
    _proxyModel = new CitySortProxyModel(this);

    _baseModel->addCities(Database::index.values());
    _proxyModel->setSourceModel(_baseModel);

    connect(_geoLocator, &GeoLocator::coordinatesAcquired, this, &CityHandler::handleCityCoordinates);
}
City* CityHandler::getCurrentCity() {
    return currentCity;
}

void CityHandler::getCurrentCityCoordinates() {
    _geoLocator->getCoordinates(currentCity->name(), currentCity->voivodeship());
}

StationCoordinateModel* CityHandler::getStationMarkers() const {
    return _stationMarkers;
}

void CityHandler::updateStationMarkers() {
    _stationMarkers->clear();
    for (const auto& station : currentCity->getStations()) {
        Coordinate coordinate = station.getCoords();
        _stationMarkers->addMarker(QGeoCoordinate(coordinate.x, coordinate.y), false);
    }
}

CitySortProxyModel* CityHandler::getCities() const {
    return _proxyModel;
}
int CityHandler::getCityId(int comboBoxIndex) const {
    return _proxyModel->data(
                          _proxyModel->index(comboBoxIndex, 0),
                          CityIndexModel::IdRole
                          ).toInt();
}

StationHandler* CityHandler::stationHandler() const{
    return _stationHandler;
}

void CityHandler::citySelected(int comboBoxIndex)  {
    int cityId = getCityId(comboBoxIndex);
    currentCity = Database::getCity(cityId);
    getCurrentCityCoordinates();
    updateStationMarkers();
    _stationHandler->loadStationsForCity();
    emit cityChanged();
}

void CityHandler::handleCityCoordinates(QGeoCoordinate &coordinate) {
    emit cityCoordinatesChanged(coordinate.latitude(), coordinate.longitude());
}
