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
    QUrl buildUrl(const QString &endpoint, const QMap<QString, QString> &params);
    void fetchStationAQI(int station_id);
    void fetchStationAQI(Station &station);
    QJsonDocument getJsonFromReply(QNetworkReply *reply);
public slots:
    void handleStations();
    void handleStationAQI();
signals:
    void stationsFinished(QMap<int, City*> cities);
    void stationAQIFinished(const QJsonDocument &doc);
private:
    QNetworkAccessManager *_manager;
    QString _basePath;
};

#endif // APICLIENT_H
