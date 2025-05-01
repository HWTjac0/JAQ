//
// Created by jac on 5/1/25.
//

#include "SensorDataHandler.h"

SensorDataHandler::SensorDataHandler(ApiClient *apiClient, QObject *parent) : QObject(parent) {
    _apiClient = apiClient;
    connect(_apiClient, &ApiClient::sensorDataFinished, this , &SensorDataHandler::onDataLoaded);
}

void SensorDataHandler::loadData(int sensorId) const {
    _apiClient->fetchSensorData(sensorId, 20);
}

void SensorDataHandler::onDataLoaded(const QJsonArray &measurments) {
    qDebug() << measurments;
}

void SensorDataHandler::onCurrentSensorChanged(Sensor *sensor) const {
    if (sensor) {
        loadData(sensor->id());
    }
}
