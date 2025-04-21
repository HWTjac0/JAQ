#ifndef APICLIENT_H
#define APICLIENT_H

#include <QHash>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include "../Station/station.h"
#include "../City/city.h"

class ApiClient : public QObject
{
    Q_OBJECT
public:
    ApiClient(QObject *parent = nullptr);
    void fetchStations(int page = 1);
    QUrl buildUrl(const QString &endpoint, const QMap<QString, QString> &params = QMap<QString, QString>());
    void fetchStationAQI(int station_id);
    void fetchStationAQI(Station &station);
    void fetchSensors(int stationId);
    QJsonDocument getJsonFromReply(QNetworkReply *reply);
public slots:
    void handleStations();
    void handleSensors();
    void handleStationAQI();
signals:
    void stationsFinished(QMap<int, City*> cities);
    void stationAQIFinished(const QJsonDocument &doc);
    void sensorsFinished(QVector<Sensor> sensors, QVector<QPair<int, Indicator>> indicators);
private:
    QNetworkAccessManager *_manager;
    QString _basePath;
};

#endif // APICLIENT_H
