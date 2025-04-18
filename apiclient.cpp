#include "apiclient.h"
#include "station.h"
#include "city.h"

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
    params.insert("size", "100");
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

    QMap<QString, City> cities;
    for (auto it = stations.cbegin(); it != stations.cend(); it++) {
        Station station = Station::fromJson(it->toObject());
        if (!cities.contains(station.cityName)) {
            cities.insert(station.cityName, City(station.cityName));
        }
        cities[station.cityName].addStation(station);
    }
    emit stationsFinished(cities);
}

