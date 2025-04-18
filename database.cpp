#include "database.h"
#include <QMap>
#include <QString>
#include "city.h"
#include "apiclient.h"

Database::Database(ApiClient *client)
    : _client(client), _indexPath("db.json")
{
    if(!QFile::exists(_indexPath)) {
        client->fetchStations();
        QJsonObject index_obj;
        connect(client, &ApiClient::stationsFinished, this, [index_obj](QMap<QString, City> &cities) mutable {
            for(auto city = cities.cbegin(); city != cities.cend(); city++) {
                QVector<Station> stations = city.value().getStations();
                QJsonArray stations_json;
                foreach (const Station &station, stations) {
                    stations_json.append(QJsonValue(station.id));
                }
                index_obj.insert(city.value().name, stations_json);
            }
        });
        qDebug() << index_obj;
    }
}
