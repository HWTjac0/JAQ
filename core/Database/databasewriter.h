#ifndef DATABASEWRITER_H
#define DATABASEWRITER_H

#include <QObject>
#include <QQueue>

#include "../apiclient.h"

class DatabaseWriter : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseWriter(QObject *parent = nullptr, ApiClient *client = nullptr, QString rootPath = "");
    void writeJson(const QJsonObject &json, const QString &path);
    void writeCSV(const QTextStream &data, const QString &path);
    void fetchAllData();
    void fetchStationSensors(Station &station);
    void processNextStation();
    QJsonObject serializeCities(QMap<int, City*> cities);
    QJsonObject serializeIndicators(QMap<int, Indicator> indicators);

    static void saveSensorData(const QVector<QPair<QString, double>> &data, const QString &date, const QString &path);
public slots:
    void handleFetchedStations(QMap<int, City*> cities);
    void handleFetchedSensors(QVector<Sensor> sensors, QVector<QPair<int, Indicator>> indicators);
    void saveCompleteDatabase();
signals:
    void allStationsProcessed();
    void writeError(const QString &message);
    void indexesReady();
private:
    ApiClient *_apiClient;
    QString _rootPath;
    QMap<int, City*> _processingCities;
    QQueue<Station> _pendingStationsQueue;
    Station _currentStation;
    bool _isProcessingStations;
};

#endif // DATABASEWRITER_H
