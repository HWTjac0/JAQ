#ifndef DATABASEREADER_H
#define DATABASEREADER_H

#include <QObject>
#include "../../Entities/city.h"
#include "../../Entities/sensor.h"

class DatabaseReader : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseReader(QObject *parent = nullptr, QString rootPath = "");
    void readCityIndex();
    void readIndicators();
    QJsonObject readJson(QString path);
    Indicator parseIndicator(const QJsonObject &indicator);
    City* parseCity(const QJsonObject &cityObj, int cityId) const;
    Station parseStation(const QJsonObject &station) const;
    QVector<Sensor> parseSensors(const QJsonArray &sensors) const;
private:
    QString _rootPath;
};

#endif // DATABASEREADER_H
