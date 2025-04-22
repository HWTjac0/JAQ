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
        City *city = parseCity(it.value().toObject(), it.key().toInt());

        QJsonArray stations_json = it.value().toObject().value("stations").toArray();
        for(auto s = stations_json.cbegin(); s != stations_json.cend(); s++) {
            QJsonObject s_json = s->toObject();
            Station station ( s_json.value("id").toInt(), s_json.value("address").toString());

            city->addStation(station);
        }
        Database::addCity(it.key().toInt(), city);
    }
}

QJsonObject DatabaseReader::readJson(QString path) {
    QFile jsonFile("indexCities.json");
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray data = jsonFile.readAll();
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    return obj;
}

City *DatabaseReader::parseCity(const QJsonObject &cityObj, int cityId) const {
    return new City(
        cityObj.value("name").toString(),
        cityObj.value("voivodeship").toString(),
        cityId
        );
}

void DatabaseReader::parseStation(const QJsonArray &) const {

}


