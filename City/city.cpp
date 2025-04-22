#include "city.h"
#include <QJsonArray>

City::City(const QString &name) { _name = name; }

QString City::name() const { return _name; }
QString City::voivodeship() const { return _voivodeship; }
int City::id() const { return _id; }

City::City(const QString &name, const QString &voivodeship, int id)
    : City(name)
{
    _voivodeship = voivodeship;
    _id = id;
}

City::City(const QString &name, const QJsonArray &stations) : City(name) {
    foreach(const QJsonValue &s, stations) {
        addStation(Station(s.toInt()));
    }
}

QJsonObject City::toIndexEntry() const {
    QJsonObject obj;
    QJsonArray stations_json;
    foreach (const Station &station, _stations) {
        stations_json.append(station.toIndexEntry());
    }
    QString vship = voivodeship().toLower();
    vship.front() = vship.front().toUpper();
    obj.insert("name", name());
    obj.insert("stations", stations_json);
    obj.insert("voivodeship", vship);

    return obj;
}
void City::addStation(const Station &station) { _stations.push_back(station); }

void City::setStationsSensors(int stationId, const QVector<Sensor> &sensors) {
    for(auto& station : _stations) {
        if(station.id() == stationId) {
            station.setSensors(sensors);
            break;
        }
    }
}
QVector<Station> City::getStations() const { return _stations; }
