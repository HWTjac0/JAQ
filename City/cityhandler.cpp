#include "cityhandler.h"
#include "citysortproxymodel.h"
#include <QStringList>
#include "../core/database.h"

CityHandler::CityHandler(ApiClient *client, QObject *parent)
    : _client(client), QObject(parent)
{
    _baseModel = new CityIndexModel(this);
    _proxyModel = new CitySortProxyModel(this);
    _stationHandler = new StationHandler(this);

    _baseModel->addCities(Database::cities);
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
    _stationHandler->loadStationsForCity(cityId);
}
