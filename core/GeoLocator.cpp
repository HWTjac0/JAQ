//
// Created by jac on 5/2/25.
//

#include "GeoLocator.h"
#include <QGeoLocation>
#include <QGeoAddress>

GeoLocator::GeoLocator(QObject *parent) : QObject(parent){
    _serviceProvider = new QGeoServiceProvider("osm");
    _geocodingManager = _serviceProvider->geocodingManager();
    _geoPositionInfoSource = QGeoPositionInfoSource::createDefaultSource(this);

    _requestingUserLocation = false;
    if (_geoPositionInfoSource) {
        connect(_geoPositionInfoSource, &QGeoPositionInfoSource::positionUpdated, this, &GeoLocator::positionUpdated);
        connect(_geoPositionInfoSource, &QGeoPositionInfoSource::errorOccurred, this, &GeoLocator::positionError);
    }
}

void GeoLocator::getCoordinates(
    const QString& city,
    const QString& voivodeship) {
    QString searchedCity = QString("%1, %2, Poland").arg(city, voivodeship);
    QGeoCodeReply* reply = _geocodingManager->geocode(searchedCity);
    connect(reply, &QGeoCodeReply::finished, this, &GeoLocator::handleCityCoordinates);
}

void GeoLocator::getUserLocation() {
    if (_requestingUserLocation) {
        return;
    }
    _requestingUserLocation = true;
    // Depend on OS I am using geoclue with beacondb and it takes a lot of time
    _geoPositionInfoSource->requestUpdate(8000);
}

void GeoLocator::handleCityCoordinates() {
    auto *reply = qobject_cast<QGeoCodeReply *>(sender());
    QVector<QGeoLocation> locations = reply->locations();
    // Last location returned is center of the location for some reason
    QGeoCoordinate coordinate = locations.last().coordinate();
    emit coordinatesAcquired(coordinate);
}

void GeoLocator::positionUpdated(const QGeoPositionInfo &info) {
    _requestingUserLocation = false;
    qDebug() << "GeoLocator::positionUpdated";
    if (info.isValid()) {
        emit userLocationAcquired(info.coordinate().latitude(), info.coordinate().longitude());
    }
}

void GeoLocator::positionError(const QGeoPositionInfoSource::Error positioningError) {
    qDebug() << "GeoLocator::positionError" << positioningError;
}
