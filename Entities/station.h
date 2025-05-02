#ifndef STATION_H
#define STATION_H
#include <QJsonObject>
#include <QString>
#include "sensor.h"

struct Coordinate {
    double x;
    double y;
};

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

    void setCoords(double x, double y);
    Coordinate getCoords() const;
    static Station fromJson(const QJsonObject &obj);
private:
    int _id;
    QString _address;
    Coordinate _coord;
    QVector<Sensor> _sensors;
    Type _type;
};
#endif // STATION_H
