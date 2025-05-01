//
// Created by jac on 5/1/25.
//

#ifndef SENSORDATAHANDLER_H
#define SENSORDATAHANDLER_H
#include <QObject>

#include "core/apiclient.h"
#include "Entities/sensor.h"
#include "Models/SensorDataModel.h"
#include <QDateTime>

class SensorDataHandler : public QObject {
    Q_OBJECT
    Q_PROPERTY(SensorDataModel* sensordataModel READ getSensorDataModel CONSTANT);
public:
    explicit SensorDataHandler(ApiClient* apiClient, QObject *parent = nullptr);
    void loadData(int sensorId) const;
    Q_INVOKABLE SensorDataModel* getSensorDataModel() const;
public slots:
    void onDataLoaded(const QJsonArray &measurments);
    void onCurrentSensorChanged(Sensor* sensor) const;
signals:
    void dataLoaded(const QJsonDocument &doc);
    void dataChanged();
private:
    ApiClient* _apiClient;
    SensorDataModel* _sensorDataModel;
};



#endif //SENSORDATAHANDLER_H
