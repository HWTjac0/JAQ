#ifndef CITYHANDLER_H
#define CITYHANDLER_H
#include <QDebug>
#include <QObject>
#include "../core/apiclient.h"
#include "../Models/cityindexmodel.h"
#include "../Models/citysortproxymodel.h"
#include "stationhandler.h"
#include "core/GeoLocator.h"

class CityHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(City* currentCity READ getCurrentCity CONSTANT)
public:
    static City* currentCity;
    CityHandler(ApiClient* apiClient, StationHandler* stationHandler, QObject *parent = nullptr);
    City* getCurrentCity();
    void getCurrentCityCoordinates();
    Q_INVOKABLE CitySortProxyModel* getCities() const;
    Q_INVOKABLE int getCityId(int comboBoxIndex) const;
    Q_INVOKABLE StationHandler* stationHandler() const;
public slots:
    void citySelected(int comboBoxIndex);
    void handleCityCoordinates(QGeoCoordinate &coordinate);
signals:
    void cityChanged();
    void cityCoordinatesChanged(double latitude, double longitude);
private:
    ApiClient *_client;
    CityIndexModel  *_baseModel;
    CitySortProxyModel *_proxyModel;
    StationHandler *_stationHandler;
    GeoLocator *_geoLocator;
};

#endif // CITYHANDLER_H
