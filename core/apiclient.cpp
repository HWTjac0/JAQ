#include "apiclient.h"
#include "../Entities/station.h"
#include "../Entities/city.h"
#include "../Entities/sensor.h"

ApiClient::ApiClient(QObject *parent)
    : QObject(parent)
{
    _manager = new QNetworkAccessManager(this);
    _basePath = QString("https://api.gios.gov.pl/pjp-api/v1/rest");
}

QUrl ApiClient::buildUrl(const QString &endpoint,
                         const QMap<QString, QString> &params)
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

void ApiClient::fetchSensors(int stationId) {
    QMap<QString, QString> params {{"size", "20"}};
    QUrl url = buildUrl("/station/sensors/" + QString::number(stationId), params);
    QNetworkRequest req(url);
    QNetworkReply *reply = _manager->get(req);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::handleSensors);
}

void ApiClient::fetchSensorData(int sensorId, int hours) {
    QMap<QString, QString> params {{"size", QString::number(hours)}};
    QUrl url = buildUrl("/data/getData/" + QString::number(sensorId), params);
    QNetworkRequest req(url);
    QNetworkReply *reply = _manager->get(req);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::handleSensorData);
}

void ApiClient::fetchArchiveSensorData(int sensorId, const QString &begin, const QString &end) {
    qDebug() << begin << " " << end;
    QMap<QString, QString> params {{"dateFrom", begin}, {"dateTo", end}, {"size", "400"}};
    QUrl url = buildUrl("/archivalData/getDataBySensor/" + QString::number(sensorId), params);
    QNetworkRequest req(url);
    QNetworkReply *reply = _manager->get(req);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::handleArchiveData);

}

void ApiClient::handleSensors() {
    QJsonObject data = getJsonFromReply(qobject_cast<QNetworkReply *>(sender())).object();
    QJsonArray sensors_json = data["Lista stanowisk pomiarowych dla podanej stacji"].toArray();
    QVector<Sensor> sensors;
    QVector<QPair<int, Indicator>> indicators;
    for(const auto &s : std::as_const(sensors_json)) {
        QJsonObject sens = s.toObject();
        int sensorId = sens.value("Identyfikator stanowiska").toInt();
        int indicatorId = sens.value("Id wskaźnika").toInt();
        QString indicatorName =  sens.value("Wskaźnik").toString();
        QString indicatorCode = sens.value("Wskaźnik - wzór").toString();
        sensors.append(Sensor(sensorId, indicatorId));
        indicators.append(QPair<int, Indicator>(indicatorId, Indicator{.code = indicatorCode, .name = indicatorName}));
    }
    emit sensorsFinished(sensors, indicators);
}

void ApiClient::fetchStations(int page)
{
    QMap<QString, QString> params;
    params.insert("size", "50");
    QUrl url = buildUrl("/station/findAll", params);
    QNetworkRequest request(url);
    QNetworkReply *reply = _manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::handleStations);
}

void ApiClient::fetchStationAQI(int station_id) {
    QUrl url = buildUrl("/aqindex/getIndex/" + QString::number(station_id));
    QNetworkRequest req(url);
    QNetworkReply *reply = _manager->get(req);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::handleStationAQI);
}

QJsonDocument ApiClient::getJsonFromReply(QNetworkReply *reply) {
    reply->deleteLater();
    return QJsonDocument::fromJson(reply->readAll());
}

void ApiClient::handleStationAQI() {
    QJsonDocument doc = getJsonFromReply(qobject_cast<QNetworkReply *>(sender()));
    emit stationAQIFinished(doc);
}

void ApiClient::handleSensorData() {
    QJsonObject data = getJsonFromReply(qobject_cast<QNetworkReply *>(sender())).object();
    QJsonArray measurments = data["Lista danych pomiarowych"].toArray();

    if (!measurments.isEmpty()) {
        emit sensorDataFinished(measurments);
    }
}

void ApiClient::handleArchiveData() {
    QJsonObject data = getJsonFromReply(qobject_cast<QNetworkReply *>(sender())).object();
    QJsonArray measurments = data["Lista archiwalnych wyników pomiarów"].toArray();
    if (!measurments.isEmpty()) {
        emit sensorDataFinished(measurments);
    }
}

void ApiClient::handleStations()
{
    QJsonObject data = getJsonFromReply(qobject_cast<QNetworkReply *>(sender())).object();
    QJsonArray stations = data["Lista stacji pomiarowych"].toArray();

    // city map index container
    QMap<int, City*> cities;
    for (auto it = stations.cbegin(); it != stations.cend(); it++) {
        QJsonObject station_json = it->toObject();
        Station station = Station::fromJson(station_json);
        // Get list of cities into the map to create index
        int city_id = station_json.value("Identyfikator miasta").toInt();

        auto cityIt = cities.find(city_id);
        if (cityIt == cities.end()) {
            QString station_cityName = station_json.value("Nazwa miasta").toString();
            QString voivodeship = station_json.value("Województwo").toString();
            QString commune = station_json.value("Gmina").toString();

            QString county = station_json.value("Powiat").toString();
            county.front() = county.front().toUpper();

            City *city = new City(station_cityName, voivodeship, county, commune , city_id);
            cityIt = cities.insert(city_id, city);
        }
        cityIt.value()->addStation(station);
    }
    emit stationsFinished(cities);
}
