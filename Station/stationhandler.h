#ifndef STATIONHANDLER_H
#define STATIONHANDLER_H
#include "stationmodel.h"
#include "station.h"

class StationHandler : public QObject
{
    Q_OBJECT
public:
    explicit StationHandler(QObject *parent = nullptr);
    void loadStationsForCity(int cityId);
    Q_INVOKABLE StationModel* stationModel() const;
private:
    StationModel *_stationModel;
    Station *_currentStation;
};

#endif // STATIONHANDLER_H
