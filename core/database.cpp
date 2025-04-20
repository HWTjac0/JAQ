#include "database.h"
#include <QMap>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include "../City/city.h"
#include "apiclient.h"

QMap<int, City*> Database::index;
QList<City*> Database::cities;

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
    QJsonObject index_obj;
    QString indexPath = _indexPath;
    connect(
        _client,
        &ApiClient::stationsFinished,
        this,
        [index_obj, indexPath, this](QMap<int, City*> cities) mutable {
            for(auto city = cities.cbegin(); city != cities.cend(); city++) {
                index_obj.insert(QString::number(city.value()->id()), city.value()->toIndexEntry());
            }
            writeJson(index_obj, indexPath);
            // QFile file(indexPath);
            // try {
            //     file.open(QIODevice::WriteOnly | QIODevice::Text);
            //     QJsonDocument doc(index_obj);
            //     qint64 bytes_written = file.write(doc.toJson());
            //     if(bytes_written == -1) {
            //         throw std::runtime_error("Failed to write index database");
            //     }
            //     file.close();
            // } catch (std::exception &e) {
            //     qWarning() << "Error: " << e.what();
            // } catch (...) {
            //     qWarning() << "Error writing index database";
            // }
            qDeleteAll(cities);
            emit dbPopulated();
        });
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
            QJsonObject station = s->toObject();
            city->addStation(Station(
                station.value("id").toInt(),
                station.value("address").toString()
                ));
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
