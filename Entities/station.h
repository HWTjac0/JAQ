#ifndef STATION_H
#define STATION_H
#include <QJsonObject>
#include <QString>
#include "sensor.h"

class Station
{
public:
    enum Type {
        Automatic,
        Manual
    };
    int cityId;
    Station() = default;
    Station(const int id);
    Station(const int id, const QString &address);
    Station(const int id, const QString &address, Type type);
    QJsonObject toIndexEntry() const;
    int id() const;
    QString address() const;
    void setId(int id);
    void setAddress(const QString &address);
    void setType(Type type);
    Type getType() const;
    QString getTypeString() const;
    QList<Sensor> getSensors() const;
    Sensor getSensorById(int sensorId) const;
    void setSensors(const QVector<Sensor> &sensors);
    static Station fromJson(const QJsonObject &obj)
    {
        Station station;
        station.setAddress(obj.value("Ulica").toString());
        station.setId(obj.value("Identyfikator stacji").toInt());

        return station;
    }
private:
    int _id;
    QString _address;
    QVector<Sensor> _sensors;
    Type _type;
};
#endif // STATION_H
