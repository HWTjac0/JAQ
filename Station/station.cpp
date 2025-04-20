#include "station.h"
#include <QJsonObject>

void Station::setAQIStatus(QString &status) {
    aqi_status = status;
}

Station::Station(const int id) {
    this->id = id;
}

Station::Station(const int id, const QString &address)
    : Station(id) {
    this->address = address;
}

QJsonObject Station::toIndexEntry() const {
    QJsonObject obj;
    obj.insert("id", this->id);
    obj.insert("address", this->address);

    return obj;
}
