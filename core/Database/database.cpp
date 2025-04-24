#include "database.h"
#include <QMap>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include "../../Entities/city.h"
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

Indicator Database::getIndicator(int indicatorId){
    return indicatorIndex.value(indicatorId);
}

City* Database::getCity(int city_id) {
    auto city_it = Database::index.find(city_id);
    if(city_it == Database::index.end()) {
        return nullptr;
    }
    return city_it.value();
}
