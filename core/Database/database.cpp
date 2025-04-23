#include "database.h"
#include <QMap>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include "../../City/city.h"
#include "../apiclient.h"

QMap<int, City*> Database::index;
QMap<int, Indicator> Database::indicatorIndex;

Database::Database(ApiClient *client, QObject* parent)
    : _client(client), _indexPath("db.json")
{
    _writer = new DatabaseWriter(this, _client);
    _reader = new DatabaseReader(this);
    if(!QFile::exists("indexCities.json")){
        _writer->fetchAllData();
    }
    _reader->readCityIndex();
    if(indicatorIndex.size() == 0) {
        _reader->readIndicators();
    }
}

void Database::addCity(int cityId, City *city){
    index.insert(cityId, city);
}

void Database::addIndicator(int indicatorId, Indicator indicator){
    indicatorIndex.insert(indicatorId, indicator);
}

void Database::init() {
    QFile index_file("indexCities.json");
    index_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray data = index_file.readAll();
    QJsonObject index = QJsonDocument::fromJson(data).object();
    for(auto it = index.constBegin(); it != index.constEnd(); it++) {
        City *city = new City(
            it.value().toObject().value("name").toString(),
            it.value().toObject().value("voivodeship").toString(),
            it.key().toInt()
            );
        QJsonArray stations_json = it.value().toObject().value("stations").toArray();
        for(auto s = stations_json.cbegin(); s != stations_json.cend(); s++) {
            QJsonObject s_json = s->toObject();
            Station station ( s_json.value("id").toInt(), s_json.value("address").toString());
            city->addStation(station);
        }
        Database::index.insert(
            it.key().toInt(),
            city
            );
    }
}

City* Database::getCity(int city_id) {
    auto city_it = Database::index.find(city_id);
    if(city_it == Database::index.end()) {
        return nullptr;
    }
    return city_it.value();
}
