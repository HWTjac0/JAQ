#include "cityhandler.h"
#include "../Models/citysortproxymodel.h"
#include <QStringList>
#include "../core/Database/database.h"

City *CityHandler::currentCity = nullptr;

CityHandler::CityHandler(ApiClient *client, QObject *parent)
    : QObject(parent), _client(client)
{
    _baseModel = new CityIndexModel(this);
    _proxyModel = new CitySortProxyModel(this);
    _stationHandler = new StationHandler(client, this);

    _baseModel->addCities(Database::index.values());
    _proxyModel->setSourceModel(_baseModel);

    connect(this, &CityHandler::cityChanged, _stationHandler->sensorHandler(), &SensorHandler::onCityChanged);
}

QString CityHandler::currentCityName() {
    return currentCity ? currentCity->name() : QString();
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
    _stationHandler->loadStationsForCity();
    emit cityChanged();
}
