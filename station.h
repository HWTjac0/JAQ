#ifndef STATION_H
#define STATION_H
#include <QJsonObject>
#include <QString>

class Station
{
public:
    int id;
    QString cityName;
    QString region;
    QString aqi_status;
    void setAQIStatus(QString &status);
    Station() = default;
    Station(const int city);
    static Station fromJson(const QJsonObject &obj)
    {
        Station station;
        station.cityName = obj["Nazwa miasta"].toString();
        station.id = obj["Identyfikator stacji"].toInt();
        station.region = obj["Województwo"].toString();
        return station;
    }
};
#endif // STATION_H
