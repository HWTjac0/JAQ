#include "station.h"
#include <QJsonObject>
#include <QJsonArray>
Station::Station() {
    _id = 0;
}
Station::Station(const int id) : _id(id) {}
Station::Station(const int id, const QString &address)
    : Station(id) {
    this->_address = address;
}
Station::Station(const int id, const QString &address, Station::Type type) :
    Station(id, address) {
    _type = type;
}


QJsonObject Station::toIndexEntry() const {
    QJsonObject obj;
    obj.insert("id", _id);
    obj.insert("address", _address);

    QJsonObject coords;
    coords.insert("x", _coord.x);
    coords.insert("y", _coord.y);
    obj.insert("coordinate", coords);

    QJsonArray sensors;
    for(auto s : _sensors) {
        QJsonObject sensor_obj;
        sensor_obj.insert("id", s.id());
        sensor_obj.insert("indicator_id", s.indicatorId());
        sensors.append(sensor_obj);
    }
    obj.insert("sensors", sensors);
    return obj;
}
int Station::id() const { return _id; }
QString Station::address() const { return _address; }
void Station::setId(int id) {
    _id = id;
}

void Station::setAddress(const QString &address) {
    _address = address;
}

void Station::setType(Type type) {
    _type = type;
}

Station::Type Station::getType() const {
    return _type;
}

QString Station::getTypeString() const {
    switch (_type) {
        case Manual: return "manualna";
        case Automatic: return "automatyczna";
        default: return "automatyczna";
    }
}

QList<Sensor> Station::getSensors() const {
    return _sensors;
}

Sensor Station::getSensorById(int sensorId) const {
    for(const auto &sensor : _sensors) {
        if(sensor.id() == sensorId) {
            return sensor;
        }
    }
    return Sensor();
}

void Station::setSensors(const QVector<Sensor> &sensors){
    for(auto s : sensors) {
        _sensors.append(s);
    }
}

void Station::setCoords(double x, double y) {
    _coord = Coordinate {.x = x, .y = y};
}

Coordinate Station::getCoords() const {
    return _coord;
}

Station Station::fromJson(const QJsonObject &obj) {
    Station station;
    station.setAddress(obj.value("Ulica").toString());
    station.setId(obj.value("Identyfikator stacji").toInt());
    station.setCoords(
        obj.value("WGS84 φ N").toString().toDouble(),
        obj.value("WGS84 λ E").toString().toDouble()
    );
    return station;
}

