#include "sensorhandler.h"
#include "stationhandler.h"
#include "core/AppContext.h"
Sensor SensorHandler::currentSensor;
SensorHandler::SensorHandler(ApiClient* apiClient, QObject *parent)
    : QObject{parent} {
    _client = apiClient;
    _sensorModel = new SensorModel(this);
    currentSensor = Sensor();
}

SensorModel* SensorHandler::sensorModel() const {
    return _sensorModel;
}
void SensorHandler::loadSensorsForStation() {
    QList<Sensor> sensors = StationHandler::currentStation.getSensors();
    _sensorModel->setSensors(sensors);
}

void SensorHandler::sensorSelected(int sensorId) {
    currentSensor = StationHandler::currentStation.getSensorById(sensorId);
   emit currentSensorChanged(&currentSensor);
}

void SensorHandler::onCityChanged() {
    _sensorModel->clear();
}
