#include "databasereader.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "database.h"

DatabaseReader::DatabaseReader(QObject *parent, QString rootPath)
    : QObject{parent} {
    _rootPath = rootPath;
}

void DatabaseReader::readCityIndex() {
    QJsonObject index = readJson("indexCities.json");
    for(auto it = index.constBegin(); it != index.constEnd(); it++) {
        int cityId = it.key().toInt();
        City *city = parseCity(it.value().toObject(), cityId);

        QJsonArray stations_json = it.value().toObject().value("stations").toArray();
        for(auto s = stations_json.cbegin(); s != stations_json.cend(); s++) {
            QJsonObject s_json = s->toObject();
            city->addStation(parseStation(s_json));
        }
        Database::addCity(cityId, city);
    }
}

void DatabaseReader::readIndicators() {
    QJsonObject index = readJson("indexIndicators.json");
    for(auto it = index.constBegin(); it != index.constEnd(); it++) {
        int indicatorId = it.key().toInt();
        Database::addIndicator(indicatorId, parseIndicator(it.value().toObject()));
    }
}

QJsonObject DatabaseReader::readJson(QString path) {
    QFile jsonFile(path);
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray data = jsonFile.readAll();
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    return obj;
}

Indicator DatabaseReader::parseIndicator(const QJsonObject &indicator)
{
    return Indicator{
        .code = indicator.value("name").toString(),
        .name = indicator.value("code").toString()
    };
}

City *DatabaseReader::parseCity(const QJsonObject &cityObj, int cityId) const {
    return new City(
        cityObj.value("name").toString(),
        cityObj.value("voivodeship").toString(),
        cityObj.value("county").toString(),
        cityObj.value("commune").toString(),
        cityId
        );
}

Station DatabaseReader::parseStation(const QJsonObject &station) const {
    Station s(station.value("id").toInt(), station.value("address").toString());
    QJsonArray sensors = station.value("sensors").toArray();
    s.setSensors(parseSensors(sensors));
    return s;
}

QVector<Sensor> DatabaseReader::parseSensors(const QJsonArray &sensors) const {
    QVector<Sensor> s_vec;
    for(auto sensor : sensors) {
        QJsonObject s_json = sensor.toObject();
        s_vec.emplaceBack(s_json.value("id").toInt(), s_json.value("indicator_id").toInt());
    }
    return s_vec;
}


