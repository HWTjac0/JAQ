#include "apiclient.h"

ApiClient::ApiClient(QObject *parent)
    : QObject(parent) {
    _manager = new QNetworkAccessManager(this);
    _basePath = QString("https://api.gios.gov.pl/pjp-api/v1/rest");
}

QUrl ApiClient::buildUrl(
    const QString &endpoint,
    const QMap<QString, QString> &params = QMap<QString, QString>()
    ) {
    QUrl url(_basePath + endpoint);
    QUrlQuery query;
    if(!params.empty()) {
        for(auto it = params.cbegin(); it != params.cend(); it++) {
            query.addQueryItem(it.key(), it.value());
        }
    }
    url.setQuery(query);

    return url;
}

void ApiClient::fetchStations(int page) {
    QMap<QString, QString> params;
    params.insert("size", "5");
    QUrl url = buildUrl("/station/findAll", params);
    QNetworkRequest request(url);
    QNetworkReply *reply = _manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::handleStations);
}

void ApiClient::fetchStationPosts(int station_id) {
    QUrl url = buildUrl("/station/sensors/" + QString::number(station_id));
    QNetworkRequest request(url);
    QNetworkReply *reply =  _manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        this->handleStationPosts(reply);
    });
}

class Station {
public:
    int id;
    QString cityName;
    QString region;

    static Station fromJson(const QJsonObject &obj) {
        Station station;
        station.cityName = obj["Nazwa miasta"].toString();
        station.id = obj["Identyfikator stacji"].toInt();
        station.region = obj["Województwo"].toString();
        return station;
    }
};

class City {
public:
    QString name;
    City() = default;
    City(const QString& name) {
        this->name = name;
    }
    void addStation(const Station& station) {
        _stations.push_back(station);
    }
    QVector<Station> getStations() const {
        return _stations;
    }
    void debugStations() const {
        for(const auto &s : _stations) {
            qDebug() << s.id;
        }
    }
private:
    QVector<Station> _stations;
};

void ApiClient::handleStations() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QByteArray responseData = reply->readAll();
    QJsonObject data = QJsonDocument::fromJson(responseData).object();
    QJsonArray stations = data["Lista stacji pomiarowych"].toArray();

    QMap<QString, City> cities;
    for(auto it = stations.cbegin(); it != stations.cend(); it++) {
        Station station = Station::fromJson(it->toObject());
        if(!cities.contains(station.cityName)) {
            cities.insert(station.cityName, City(station.cityName));
        }
        cities[station.cityName].addStation(station);
    }
    for(auto city = cities.cbegin(); city != cities.cend(); city++) {
        QVector<Station> cityStations= city.value().getStations();
        qDebug() << city.value().name;
        for (auto station = cityStations.cbegin(); station != cityStations.cend(); station++) {
            fetchStationPosts(station->id);
        }
    }
    reply->deleteLater();

}

void ApiClient::handleStationPosts(QNetworkReply *reply) {
    QByteArray responseData = reply->readAll();
    QJsonObject data = QJsonDocument::fromJson(responseData).object();
    QJsonArray posts = data["Lista stanowisk pomiarowych dla podanej stacji"].toArray();
    for(auto it = posts.cbegin(); it != posts.cend(); it++) {
        qDebug() << "\t" << it->toObject();
    }
    reply->deleteLater();

}
