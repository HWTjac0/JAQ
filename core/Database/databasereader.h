#ifndef DATABASEREADER_H
#define DATABASEREADER_H

#include <QObject>
#include "../../City/city.h"

class DatabaseReader : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseReader(QObject *parent = nullptr, QString rootPath = "");
    void readCityIndex();
    void readIndicators();
    QJsonObject readJson(QString path);
    void parseIndicators();
    City* parseCity(const QJsonObject &cityObj, int cityId) const;
    void parseStation(const QJsonArray &stationsArr) const;
    void parseSensors();
private:
    QString _rootPath;
};

#endif // DATABASEREADER_H
