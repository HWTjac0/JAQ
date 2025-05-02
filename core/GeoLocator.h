//
// Created by jac on 5/2/25.
//

#ifndef GEOLOCATOR_H
#define GEOLOCATOR_H
#include <QObject>
#include <QGeoCodingManager>
#include <QGeoServiceProvider>

class GeoLocator : public QObject {
    Q_OBJECT
public:
    explicit GeoLocator(QObject *parent = nullptr);
    void getCoordinates(const QString &city, const QString &voivodeship);
public slots:
    void handleCityCoordinates();
signals:
    void coordinatesAcquired(QGeoCoordinate &coordinates);
private:
    QGeoCodingManager* _geocodingManager;
    QGeoServiceProvider* _serviceProvider;
};



#endif //GEOLOCATOR_H
