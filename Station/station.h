#ifndef STATION_H
#define STATION_H
#include <QJsonObject>
#include <QString>

class Station
{
public:
    int id;
    QString cityName;
    QString address;
    QString aqi_status;
    void setAQIStatus(QString &status);
    Station() = default;
    Station(const int city);
    Station(const int id, const QString &address);
    static Station fromJson(const QJsonObject &obj)
    {
        Station station;
        station.cityName = obj.value("Nazwa miasta").toString();
        station.address  = obj.value("Ulica").toString();
        station.id = obj.value("Identyfikator stacji").toInt();
        return station;
    }
    QJsonObject toIndexEntry() const;
};
#endif // STATION_H
