#ifndef CITY_H
#define CITY_H
#include <QString>
#include "station.h"
#include <QVector>
#include <QObject>

class City : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT);
    Q_PROPERTY(QString voivodeship READ voivodeship CONSTANT);
    Q_PROPERTY(QString county READ county CONSTANT);
    Q_PROPERTY(QString commune READ commune CONSTANT);
    Q_PROPERTY(int id READ id CONSTANT);

public:

    QString name() const;
    QString voivodeship() const;
    QString county() const;
    QString commune() const;
    int id() const;

    City() = default;
    City(const QString &name);
    City(const QString &name, const QString &voivodeship, const QString &county, const QString &commune, int id);
    City(const QString &name, const QJsonArray &stations);
    QJsonObject toIndexEntry() const;
    void addStation(const Station &station);
    QList<Station> getStations() const;
    Station getStationById(int stationId) const;
    void setStationsSensors(int stationId, const QVector<Sensor>& sensors);
private:
    QVector<Station> _stations;
    QString _name;
    QString _voivodeship;
    QString _commune;
    QString _county;
    int _id;
};
#endif // CITY_H
