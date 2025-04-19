#include "database.h"
#include <QMap>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include "city.h"
#include "apiclient.h"

QMap<QString, City> Database::index;
QStringList Database::cities;

Database::Database(ApiClient *client)
    : _client(client), _indexPath("db.json")
{
    QString indexPath = _indexPath;
    if(!QFile::exists(_indexPath)) {
        client->fetchStations();
        QJsonObject index_obj;
        connect(client, &ApiClient::stationsFinished, this, [index_obj, indexPath](QMap<QString, City> &cities) mutable {
            for(auto city = cities.cbegin(); city != cities.cend(); city++) {
                QVector<Station> stations = city.value().getStations();
                QJsonArray stations_json;
                foreach (const Station &station, stations) {
                    stations_json.append(QJsonValue(station.id));
                }
                index_obj.insert(city.value().name, stations_json);
            }
            QFile file(indexPath);
            try {
                file.open(QIODevice::WriteOnly);
                QJsonDocument doc(index_obj);
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
        });
    }
}

void Database::init() {
    QFile index_file(_indexPath);
    index_file.open(QIODevice::ReadOnly);
    QByteArray data = index_file.readAll();
    QJsonObject index = QJsonDocument::fromJson(data).object();
    for(auto it = index.constBegin(); it != index.constEnd(); it++) {
        Database::cities.append(it.key());
        Database::index.insert(
            it.key(),
            City(it.key(), it.value().toArray())
        );
    }
}
