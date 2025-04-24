#include "sensor.h"
#include "../core/Database/database.h"
Sensor::Sensor() {}

Sensor::Sensor(int id, int indicatorId)
    : _id(id), _indicatorId(indicatorId){}

int Sensor::indicatorId() const { return _indicatorId; }

Indicator Sensor::getIndicator() const {
    return Database::getIndicator(_indicatorId);
}
int Sensor::id() const { return _id; }
