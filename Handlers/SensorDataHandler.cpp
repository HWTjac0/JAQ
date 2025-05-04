//
// Created by jac on 5/1/25.
//

#include "SensorDataHandler.h"

#include "core/AppContext.h"
#include "core/PathManager.h"

SensorDataHandler::SensorDataHandler(ApiClient *apiClient, QObject *parent) : QObject(parent) {
    _apiClient = apiClient;
    _sensorDataModel = new SensorDataModel(this);
    connect(_apiClient, &ApiClient::sensorDataFinished, this , &SensorDataHandler::onDataLoaded);
}

void SensorDataHandler::loadData(int sensorId) const {
    _apiClient->fetchSensorData(sensorId, 20);
}

void SensorDataHandler::saveData() const {
    auto& context =  *AppContext::getInstance();
    int currentStationId = context.getStationHandler()->currentStation.id();
    int currentSensorId = context.getSensorHandler()->currentSensorId();
    if (currentSensorId and currentStationId) {
        Database::saveSensorData(currentStationId, currentSensorId, _measurements);
    }
}

SensorDataModel * SensorDataHandler::getSensorDataModel() const {
    return _sensorDataModel;
}

void SensorDataHandler::getArchiveData(const QDateTime &begin, const QDateTime &end) const {
    QString beginParam = begin.toString("yyyy-MM-dd") + QStringLiteral("%2000%3A00");
    QString endParam = end.toString("yyyy-MM-dd") + QStringLiteral("%2000%3A00");
    int sensorId = AppContext::getInstance()->getSensorHandler()->currentSensorId();
    _apiClient->fetchArchiveSensorData(sensorId, beginParam, endParam);
}

void SensorDataHandler::onDataLoaded(const QJsonArray &data) {
    _measurements.clear();
    double min = 9999999;
    double max = 0;
    for (auto d : data) {
        QJsonObject mobj = d.toObject();
        QDateTime timestamp = QDateTime::fromString(
            mobj.value("Data").toString(),
            "yyyy-MM-dd HH:mm:ss"
            );
        double value = mobj.value("Wartość").toDouble();
        min = min < value ? min : value;
        max = max > value ? max : value;

        _measurements.emplace_back(timestamp, value);
    }
    _sensorDataModel->setData(_measurements);
    emit dataChanged();
}

void SensorDataHandler::onCurrentSensorChanged(Sensor *sensor) const {
    if (sensor) {
        loadData(sensor->id());
    }
}
