#ifndef CITYHANDLER_H
#define CITYHANDLER_H
#include <QDebug>
#include <QObject>
#include "../core/apiclient.h"
#include "../Models/cityindexmodel.h"
#include "../Models/citysortproxymodel.h"
#include "stationhandler.h"
#include "core/GeoLocator.h"
#include "Models/StationCoordinateModel.h"

class CityHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(City* currentCity READ getCurrentCity CONSTANT)
    Q_PROPERTY(StationCoordinateModel* stationMarkers READ getStationMarkers CONSTANT);
    Q_PROPERTY(QVector<QString> voivodeshipModel READ voivodeshipModel CONSTANT);
public:
    static City* currentCity;
    CityHandler(ApiClient* apiClient, StationHandler* stationHandler, QObject *parent = nullptr);

    QList<QString> getVoivodeships();
    QList<QString> voivodeshipModel();
    City* getCurrentCity();
    void getCurrentCityCoordinates();
    StationCoordinateModel* getStationMarkers() const;
    void updateStationMarkers();
    Q_INVOKABLE CitySortProxyModel* getCities() const;
    Q_INVOKABLE int getCityId(int comboBoxIndex) const;
    Q_INVOKABLE StationHandler* stationHandler() const;
    Q_INVOKABLE void getUserLocation();
public slots:
    void citySelected(int comboBoxIndex);
    void handleCityCoordinates(QGeoCoordinate &coordinate);
signals:
    void cityChanged();
    void cityCoordinatesChanged(double latitude, double longitude);
    void userLocationChanged(double latitude, double longitude);
private:
    ApiClient *_client;
    CityIndexModel  *_baseModel;
    CitySortProxyModel *_proxyModel;
    QList<QString> _voivodeshipModel;
    StationHandler *_stationHandler;
    GeoLocator *_geoLocator;
    StationCoordinateModel *_stationMarkers;
};

#endif // CITYHANDLER_H
