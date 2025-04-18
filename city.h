#ifndef CITY_H
#define CITY_H
#include <QString>
#include "station.h"
#include <QVector>

class City
{
public:
    QString name;
    City() = default;
    City(const QString &name);
    void addStation(const Station &station);
    QVector<Station> getStations() const;
    void debugStations() const;
private:
    QVector<Station> _stations;
};
#endif // CITY_H
