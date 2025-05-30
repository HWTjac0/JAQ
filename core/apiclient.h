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
#include "../Entities/station.h"
#include "../Entities/city.h"

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
    void fetchSensorData(int sensorId, int hours);
    void fetchArchiveSensorData(int sensorId, const QString &begin, const QString &end);
    QJsonDocument getJsonFromReply(QNetworkReply *reply);
public slots:
    void handleStations();
    void handleSensors();
    void handleStationAQI();
    void handleSensorData();
    void handleArchiveData();
signals:
    void sensorDataFinished(const QJsonArray &measurments);
    void stationsFinished(QMap<int, City*> cities);
    void stationAQIFinished(const QJsonDocument &doc);
    void sensorsFinished(QVector<Sensor> sensors, QVector<QPair<int, Indicator>> indicators);
private:
    QNetworkAccessManager *_manager;
    QString _basePath;
};

#endif // APICLIENT_H
