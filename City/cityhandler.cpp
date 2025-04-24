#include "cityhandler.h"
#include "citysortproxymodel.h"
#include <QStringList>
#include "../core/Database/database.h"

City *CityHandler::currentCity = nullptr;

CityHandler::CityHandler(ApiClient *client, QObject *parent)
    : _client(client), QObject(parent)
{
    _baseModel = new CityIndexModel(this);
    _proxyModel = new CitySortProxyModel(this);
    _stationHandler = new StationHandler(client, this);

    _baseModel->addCities(Database::index.values());
    _proxyModel->setSourceModel(_baseModel);
}

CitySortProxyModel* CityHandler::getCities() const {
    return _proxyModel;
}
int CityHandler::getCityId(int comboBoxIndex) {
    return _proxyModel->data(
                          _proxyModel->index(comboBoxIndex, 0),
                          CityIndexModel::IdRole
                          ).toInt();
}

StationHandler* CityHandler::stationHandler() const{
    return _stationHandler;
}
void CityHandler::citySelected(int comboBoxIndex) {
    int cityId = getCityId(comboBoxIndex);
    currentCity = Database::getCity(cityId);
    _stationHandler->loadStationsForCity();
}
