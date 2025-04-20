#ifndef STATIONHANDLER_H
#define STATIONHANDLER_H
#include "stationmodel.h"
#include "station.h"
#include "../core/apiclient.h"

class StationHandler : public QObject
{
    Q_OBJECT
public:
    explicit StationHandler(ApiClient *apiClient, QObject *parent = nullptr);
    void loadStationsForCity(int cityId);
    Q_INVOKABLE void getStationUrl(int stationId);
    Q_INVOKABLE StationModel* stationModel() const;
private:
    StationModel *_stationModel;
    Station *_currentStation;
    ApiClient *_apiClient;
};

#endif // STATIONHANDLER_H
