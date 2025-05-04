#ifndef STATIONHANDLER_H
#define STATIONHANDLER_H
#include <QGeoCoordinate>

#include "../Models/stationmodel.h"
#include "../Entities/station.h"
#include "../core/apiclient.h"
#include "sensorhandler.h"
class StationHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentStationAddress READ currentStationAddress CONSTANT);
    Q_PROPERTY(int currentStationId READ currentStationId CONSTANT);
    Q_PROPERTY(QGeoCoordinate currentStationCoordinate READ currentStationCoordinate CONSTANT);
    Q_PROPERTY(StationModel* stationModel READ stationModel CONSTANT);
public:
    static Station currentStation;
    explicit StationHandler(ApiClient* apiClient, SensorHandler* sensorHandler, QObject *parent = nullptr);
    void loadStationsForCity();
    Q_INVOKABLE StationModel* stationModel() const;
    SensorHandler * sensorHandler();
    QString currentStationAddress() const;
    QGeoCoordinate currentStationCoordinate() const;
    int currentStationId() const;

public slots:
    void processAQI(QJsonDocument aqiDoc);
    void stationSelected(int stationId);
signals:
    void stationChanged();
    void stationAQIAcquired(const QVariantMap &aqiStatus);
private:
    StationModel *_stationModel;
    SensorHandler *_sensorHandler;
    ApiClient *_apiClient;
};

#endif // STATIONHANDLER_H
