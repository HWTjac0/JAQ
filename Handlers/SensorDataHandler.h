//
// Created by jac on 5/1/25.
//

#ifndef SENSORDATAHANDLER_H
#define SENSORDATAHANDLER_H
#include <QObject>

#include "core/apiclient.h"
#include "Entities/sensor.h"


class SensorDataHandler : public QObject {
    Q_OBJECT
public:
    explicit SensorDataHandler(ApiClient* apiClient, QObject *parent = nullptr);
    void loadData(int sensorId) const;
public slots:
    void onDataLoaded(const QJsonArray &measurments);
    void onCurrentSensorChanged(Sensor* sensor) const;
signals:
    void dataLoaded(const QJsonDocument &doc);
private:
    ApiClient* _apiClient;
};



#endif //SENSORDATAHANDLER_H
