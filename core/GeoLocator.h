//
// Created by jac on 5/2/25.
//

#ifndef GEOLOCATOR_H
#define GEOLOCATOR_H
#include <QObject>
#include <QGeoCodingManager>
#include <QGeoServiceProvider>
#include <QGeoPositionInfoSource>
#include <QGeoPositionInfo>

class GeoLocator : public QObject {
    Q_OBJECT
public:
    explicit GeoLocator(QObject *parent = nullptr);
    void getCoordinates(const QString &city, const QString &voivodeship);
    void getUserLocation();
public slots:
    void handleCityCoordinates();
    void positionUpdated(const QGeoPositionInfo &info);
    void positionError(const QGeoPositionInfoSource::Error positioningError);
signals:
    void coordinatesAcquired(QGeoCoordinate &coordinates);
    void userLocationAcquired(double latitude, double longitude);
private:
    QGeoCodingManager* _geocodingManager;
    QGeoServiceProvider* _serviceProvider;
    QGeoPositionInfoSource* _geoPositionInfoSource;
    bool _requestingUserLocation;
};



#endif //GEOLOCATOR_H
