#include "sensorhandler.h"
#include "stationhandler.h"
Sensor SensorHandler::currentSensor;
SensorHandler::SensorHandler(QObject *parent, ApiClient *client)
    : QObject{parent}, _client(client) {
    currentSensor = Sensor();
    _sensorModel = new SensorModel(this);
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
    _client->fetchSensorData(currentSensor.id(), 24);
}

void SensorHandler::onCityChanged() {
    _sensorModel->clear();
}
