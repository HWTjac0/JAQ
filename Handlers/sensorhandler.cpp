#include "sensorhandler.h"
#include "stationhandler.h"
#include "core/AppContext.h"

QString SensorHandler::currentSensorIndicator() const {
    Indicator currentIndicator = _currentSensor.getIndicator();
    return QString("%1 (%2)").arg(currentIndicator.name, currentIndicator.code);
}

int SensorHandler::currentSensorId() const {
    return _currentSensor.id();
}

SensorHandler::SensorHandler(ApiClient* apiClient, QObject *parent)
    : QObject{parent} {
    _client = apiClient;
    _sensorModel = new SensorModel(this);
    _currentSensor = Sensor();
}

SensorModel* SensorHandler::sensorModel() const {
    return _sensorModel;
}
void SensorHandler::loadSensorsForStation() {
    QList<Sensor> sensors = StationHandler::currentStation.getSensors();
    _sensorModel->setSensors(sensors);
}

void SensorHandler::sensorSelected(int sensorId) {
    _currentSensor = StationHandler::currentStation.getSensorById(sensorId);
   emit currentSensorChanged(&_currentSensor);
}

void SensorHandler::onCityChanged() {
    _sensorModel->clear();
}
