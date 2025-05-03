#include "database.h"
#include <QMap>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <qstandardpaths.h>
#include <QTextStream>

#include "../../Entities/city.h"
#include "../apiclient.h"
#include "core/AppContext.h"
#include "core/PathManager.h"

QMap<int, City*> Database::index;
QMap<int, Indicator> Database::indicatorIndex;

Database::Database(ApiClient* apiClient, QObject* parent)
    : _indexPath("db.json")
{
    _client = apiClient;
    _writer = new DatabaseWriter(this, _client);
    _reader = new DatabaseReader(this);
}
bool Database::exists() {
    return PathManager::doesFileExist(PathManager::cityIndex());
}
void Database::init() {
    if(!exists()){
        _writer->fetchAllData();
        connect(_writer, &DatabaseWriter::indexesReady, this, [this]() {
            _reader->readCityIndex();
             if(indicatorIndex.empty()) {
                 _reader->readIndicators();
             }
            emit databaseReady();
        });
    } else {
        _reader->readCityIndex();
        if(indicatorIndex.empty()) {
            _reader->readIndicators();
        }
        emit databaseReady();
    }
}

void Database::addCity(int cityId, City *city){
    index.insert(cityId, city);
}

void Database::saveSensorData(int stationId, int sensorId, const QVector<QPair<QDateTime, double>> &values) {
    QString path = PathManager::sensorDataDirectory(stationId, sensorId);
    QMap<QString, QVector<QPair<QString, double>>> dates;
    // There might be data gathered from multiple days
    for (const auto& value : values) {
        QString date = value.first.toString("dd_MM_yyyy");
        if (!dates.contains(date)) {
            dates.insert(date, QVector<QPair<QString, double>>());
        }
        dates[date].push_back({value.first.toString("hh_mm_ss"), value.second});
    }
    for (const auto& date : dates.keys()) {
        DatabaseWriter::saveSensorData(dates.value(date), date, path);
    }
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
