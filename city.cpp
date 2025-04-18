#include "city.h"

City::City(const QString &name) { this->name = name; }
void City::addStation(const Station &station) { _stations.push_back(station); }
QVector<Station> City::getStations() const { return _stations; }
void City::debugStations() const
{
    for (const auto &s : _stations) {
        qDebug() << s.id;
    }
}
