#ifndef CITY_H
#define CITY_H
#include <QString>
#include "../Station/station.h"
#include <QVector>
#include <QObject>

class City : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT);
    Q_PROPERTY(QString voivodeship READ voivodeship CONSTANT);
    Q_PROPERTY(int id READ id CONSTANT);

public:

    QString name() const;
    QString voivodeship() const;
    int id() const;

    City() = default;
    City(const QString &name);
    City(const QString &name, const QString &voivodeship, int id);
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
    int _id;
};
#endif // CITY_H
