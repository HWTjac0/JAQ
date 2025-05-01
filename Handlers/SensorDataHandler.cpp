//
// Created by jac on 5/1/25.
//

#include "SensorDataHandler.h"

SensorDataHandler::SensorDataHandler(ApiClient *apiClient, QObject *parent) : QObject(parent) {
    _apiClient = apiClient;
    _sensorDataModel = new SensorDataModel(this);
    connect(_apiClient, &ApiClient::sensorDataFinished, this , &SensorDataHandler::onDataLoaded);
}

void SensorDataHandler::loadData(int sensorId) const {
    _apiClient->fetchSensorData(sensorId, 20);
}

SensorDataModel * SensorDataHandler::getSensorDataModel() const {
    return _sensorDataModel;
}

void SensorDataHandler::onDataLoaded(const QJsonArray &data) {
    QVector<QPair<QDateTime, double>> measurements;
    for (auto d : data) {
        QJsonObject mobj = d.toObject();
        QDateTime timestamp = QDateTime::fromString(
            mobj.value("Data").toString(),
            "yyyy-MM-dd HH:mm:ss"
            );
        double value = mobj.value("Wartość").toDouble();
        measurements.emplace_back(timestamp, value);
    }
    _sensorDataModel->setData(measurements);
}

void SensorDataHandler::onCurrentSensorChanged(Sensor *sensor) const {
    if (sensor) {
        loadData(sensor->id());
    }
}
