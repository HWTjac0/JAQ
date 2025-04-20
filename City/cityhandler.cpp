#include "cityhandler.h"
#include "citysortproxymodel.h"
#include <QStringList>
#include "../database.h"

CityHandler::CityHandler(ApiClient *client, QObject *parent)
    : _client(client), QObject(parent)
{
    _baseModel = new CityIndexModel(this);
    _proxyModel = new CitySortProxyModel(this);

    _baseModel->addCities(Database::cities);
    _proxyModel->setSourceModel(_baseModel);
}

void CityHandler::receiveText(const QString &text)
{
    qDebug() << "Received text from QML:" << text;
    emit cityChanged(text);
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
