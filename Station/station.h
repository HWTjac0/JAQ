#ifndef STATION_H
#define STATION_H
#include <QJsonObject>
#include <QString>

class Station
{
public:
    Station() = default;
    Station(const int id);
    Station(const int id, const QString &address);
    QJsonObject toIndexEntry() const;
    int id() const;
    QString address() const;
    void setId(int id);
    void setAddress(const QString &address);
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
};
#endif // STATION_H
