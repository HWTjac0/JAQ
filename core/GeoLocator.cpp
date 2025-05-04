//
// Created by jac on 5/2/25.
//

#include "GeoLocator.h"
#include <QGeoLocation>
#include <QGeoAddress>

#include "AppContext.h"
#include "Database/database.h"

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

double GeoLocator::haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    const double r = 6378;
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    const double deltaLat = lat2 - lat1;
    const double deltaLon = lon2 - lon1;

    using namespace std;
    const double a = pow(sin(deltaLat/2), 2) + cos(lat1) * cos(lat2) * pow(sin(deltaLon/2), 2);
    const double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return r * c;
}

double GeoLocator::toRadians(double deg) {
    return deg * M_PI / 180;
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
        double userLat =info.coordinate().latitude();
        double userLon = info.coordinate().longitude();
        double minDistance = std::numeric_limits<double>::max();
        int nearestStationId;
        int nearestCityId;
        for (const auto& city : Database::index.values()) {
            for (const auto& station : city->getStations()) {
                double distance = haversineDistance(userLat, userLon, station.getCoords().x, station.getCoords().y);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestStationId = station.id();
                    nearestCityId = city->id();
                }
            }
        }
        AppContext::getInstance()->getCityHandler()->changeCity(nearestCityId);
        AppContext::getInstance()->getStationHandler()->stationSelected(nearestStationId);
        emit userLocationAcquired(userLat, userLon);
    }
}

void GeoLocator::positionError(const QGeoPositionInfoSource::Error positioningError) {
    qDebug() << "GeoLocator::positionError" << positioningError;
}
