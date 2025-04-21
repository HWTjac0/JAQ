#include "station.h"
#include <QJsonObject>
#include <QJsonArray>

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
    QJsonArray sensors;
    for(auto s : _sensors) {
        sensors.append(s.id());
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

void Station::setSensors(QVector<Sensor> &sensors){
    for(auto s : sensors) {
        _sensors.append(s);
    }
}

