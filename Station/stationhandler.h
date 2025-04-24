#ifndef STATIONHANDLER_H
#define STATIONHANDLER_H
#include "stationmodel.h"
#include "station.h"
#include "../core/apiclient.h"
#include "Sensor/sensorhandler.h"
class StationHandler : public QObject
{
    Q_OBJECT
public:
    static Station currentStation;
    explicit StationHandler(ApiClient *apiClient, QObject *parent = nullptr);
    void loadStationsForCity();
    Q_INVOKABLE StationModel* stationModel() const;
    SensorHandler * sensorHandler();
public slots:
    void stationSelected(int stationId);
private:
    StationModel *_stationModel;
    SensorHandler *_sensorHandler;
    ApiClient *_apiClient;
};

#endif // STATIONHANDLER_H
