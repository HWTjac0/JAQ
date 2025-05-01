//
// Created by jac on 5/1/25.
//

#ifndef APPCONTEXT_H
#define APPCONTEXT_H
#include <QObject>

#include "Handlers/cityhandler.h"
#include "Handlers/stationhandler.h"
#include "Handlers/sensorhandler.h"
#include "apiclient.h"
#include "Handlers/SensorDataHandler.h"

class AppContext : public QObject {
    Q_OBJECT
    Q_PROPERTY(CityHandler* cityHandler READ getCityHandler CONSTANT);
    Q_PROPERTY(StationHandler* stationHandler READ getStationHandler CONSTANT);
    Q_PROPERTY(SensorHandler* sensorHandler READ getSensorHandler CONSTANT);
    Q_PROPERTY(SensorDataHandler* sensorDataHandler READ getSensorDataHandler CONSTANT);
public:
    void initialize();
    static AppContext& getInstance();
    [[nodiscard]] CityHandler* getCityHandler() const;
    [[nodiscard]] StationHandler* getStationHandler() const;
    [[nodiscard]] SensorHandler* getSensorHandler() const;
    [[nodiscard]] SensorDataHandler* getSensorDataHandler() const;
    [[nodiscard]] ApiClient* getApiClient() const;
private:
    explicit AppContext(QObject* parent = nullptr);
    static AppContext* _instance;

    QScopedPointer<CityHandler> _cityHandler;
    QScopedPointer<StationHandler> _stationHandler;
    QScopedPointer<SensorHandler> _sensorHandler;
    QScopedPointer<SensorDataHandler> _sensorDataHandler;
    QScopedPointer<ApiClient> _apiClient;
};



#endif //APPCONTEXT_H
