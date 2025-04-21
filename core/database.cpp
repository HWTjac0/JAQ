#include "database.h"
#include <QMap>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include "../City/city.h"
#include "apiclient.h"

QMap<int, City*> Database::index;
QList<City*> Database::cities;
QMap<int, Indicator> Database::indicatorIndex;


Database::Database(ApiClient *client)
    : _client(client), _indexPath("db.json")
{
    if(!QFile::exists(_indexPath)) {
        populate();
        connect(this, &Database::dbPopulated, this, &Database::init);
    } else {
        init();
    }
}
// index looks as follow
//     id: {
//         name: string
//         voivodeship: string
//         stations: int[]
//     }
void Database::populate() {
    _client->fetchStations();
    connect(_client, &ApiClient::stationsFinished, this, &Database::handleFetchedStations);
}

void Database::handleFetchedStations(QMap<int, City*> cities) {
    QJsonObject index_obj;
    int pendingRequests = 0;
    for(auto city = cities.cbegin(); city != cities.cend(); city++) {
        for(auto& station : city.value()->getStations()) {
            _client->fetchSensors(station.id());
            connect(_client,
                    &ApiClient::sensorsFinished,
                    this,
                    [station](QVector<Sensor> sensors,
                              QVector<QPair<int, Indicator>> indicators) mutable {
                        station.setSensors(sensors);
                        for(const auto& i : indicators) {
                            Database::indicatorIndex.insert(i.first, i.second);
                        }
                    });
        }
        index_obj.insert(QString::number(city.value()->id()), city.value()->toIndexEntry());
        qDebug() << city.value()->toIndexEntry();
    }
    writeJson(index_obj, _indexPath);
    qDeleteAll(cities);
}

void Database::writeJson(const QJsonObject &json, const QString &path) {
    QFile file(path);
    try {
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QJsonDocument doc(json);
        qint64 bytes_written = file.write(doc.toJson());
        if(bytes_written == -1) {
            throw std::runtime_error("Failed to write index database");
        }
        file.close();
    } catch (std::exception &e) {
        qWarning() << "Error: " << e.what();
    } catch (...) {
        qWarning() << "Error writing index database";
    }
}

void Database::init() {
    QFile index_file(_indexPath);
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
        Database::cities.append(city);
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
