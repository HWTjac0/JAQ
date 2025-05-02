//
// Created by jac on 5/2/25.
//

#include "GeoLocator.h"
#include <QGeoLocation>
#include <QGeoAddress>

GeoLocator::GeoLocator(QObject *parent) : QObject(parent){
    _serviceProvider = new QGeoServiceProvider("osm");
    _geocodingManager = _serviceProvider->geocodingManager();
}

void GeoLocator::getCoordinates(
    const QString& city,
    const QString& voivodeship) {
    QString searchedCity = QString("%1, %2, Poland").arg(city, voivodeship);
    QGeoCodeReply* reply = _geocodingManager->geocode(searchedCity);
    connect(reply, &QGeoCodeReply::finished, this, &GeoLocator::handleCityCoordinates);
}

void GeoLocator::handleCityCoordinates() {
    auto *reply = qobject_cast<QGeoCodeReply *>(sender());
    QVector<QGeoLocation> locations = reply->locations();
    // Last location returned is center of the location for some reason
    QGeoCoordinate coordinate = locations.last().coordinate();
    emit coordinatesAcquired(coordinate);
}
