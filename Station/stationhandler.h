#ifndef STATIONHANDLER_H
#define STATIONHANDLER_H
#include "stationmodel.h"
#include "station.h"
#include "../core/apiclient.h"

class StationHandler : public QObject
{
    Q_OBJECT
public:
    static Station currentStation;
    explicit StationHandler(ApiClient *apiClient, QObject *parent = nullptr);
    void loadStationsForCity(int cityId);
    Q_INVOKABLE StationModel* stationModel() const;
public slots:
    void stationSelected(int stationId);
private:
    StationModel *_stationModel;
    ApiClient *_apiClient;
};

#endif // STATIONHANDLER_H
