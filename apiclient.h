#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QHash>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class ApiClient : public QObject
{
    Q_OBJECT
public:
    ApiClient(QObject *parent = nullptr);
    void fetchStations(int page = 1);
    void fetchStationPosts(int station_id);
    QUrl buildUrl(const QString &endpoint, const QMap<QString, QString> &params);
public slots:
    void handleStations();
    void handleStationPosts(QNetworkReply *reply);
private:
    QNetworkAccessManager *_manager;
    QString _basePath;
};

#endif // APICLIENT_H
