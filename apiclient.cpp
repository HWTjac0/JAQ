#include "apiclient.h"
#include "station.h"
#include "City/city.h"

ApiClient::ApiClient(QObject *parent)
    : QObject(parent)
{
    _manager = new QNetworkAccessManager(this);
    _basePath = QString("https://api.gios.gov.pl/pjp-api/v1/rest");
}

QUrl ApiClient::buildUrl(const QString &endpoint,
                         const QMap<QString, QString> &params = QMap<QString, QString>())
{
    QUrl url(_basePath + endpoint);
    QUrlQuery query;
    if (!params.empty()) {
        for (auto it = params.cbegin(); it != params.cend(); it++) {
            query.addQueryItem(it.key(), it.value());
        }
    }
    url.setQuery(query);

    return url;
}

void ApiClient::fetchStations(int page)
{
    QMap<QString, QString> params;
    params.insert("size", "300");
    QUrl url = buildUrl("/station/findAll", params);
    QNetworkRequest request(url);
    QNetworkReply *reply = _manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::handleStations);
}

void ApiClient::fetchStationAQI(Station &station) {
    QUrl url = buildUrl("/aqindex/getIndex/" + QString::number(station.id));
    QNetworkRequest req(url);
    QNetworkReply *reply = _manager->get(req);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::handleStationAQI);
    connect(this, &ApiClient::stationAQIFinished, this, [station](const QJsonDocument& doc) mutable {
        QString aqi_status = doc.object()
                                 .value("AqIndex").toObject()
                                 .value("Nazwa kategorii indeksu")
                                 .toString();
        station.setAQIStatus(aqi_status);
    });
}
QJsonDocument ApiClient::getJsonFromReply(QNetworkReply *reply) {
    reply->deleteLater();
    return QJsonDocument::fromJson(reply->readAll());
}

void ApiClient::handleStationAQI() {
    QJsonDocument doc = getJsonFromReply(qobject_cast<QNetworkReply *>(sender()));
    emit stationAQIFinished(doc);
}

void ApiClient::handleStations()
{
    QJsonObject data = getJsonFromReply(qobject_cast<QNetworkReply *>(sender())).object();
    QJsonArray stations = data["Lista stacji pomiarowych"].toArray();

    QMap<int, City*> cities;
    for (auto it = stations.cbegin(); it != stations.cend(); it++) {
        QJsonObject station_json = it->toObject();
        Station station = Station::fromJson(station_json);
        int city_id = station_json.value("Identyfikator miasta").toInt();

        auto cityIt = cities.find(city_id);
        if (cityIt == cities.end()) {
            City *city = new City(station.cityName, station_json.value("Województwo").toString(), city_id);
            cityIt = cities.insert(city_id, city);
        }
        cityIt.value()->addStation(station);
        // if (!cities.contains(city_id)) {
        //     City city(station.cityName, station_json.value("Województwo").toString(), city_id);
        //     cities.insert(
        //         city_id,
        //         city
        //         );
        // }
        // if(cities.contains(city_id)){
        //     cities[city_id].addStation(station);
        // }
    }
    emit stationsFinished(cities);
}

