#include "city.h"
#include <QJsonArray>

City::City(const QString &name) { this->name = name; }

City::City(const QString &name, const QJsonArray &stations) : City(name)
{
    foreach(const QJsonValue &s, stations) {
        addStation(Station(s.toInt()));
    }
}
void City::addStation(const Station &station) { _stations.push_back(station); }
QVector<Station> City::getStations() const { return _stations; }
void City::debugStations() const
{
    for (const auto &s : _stations) {
        qDebug() << s.id;
    }
}
