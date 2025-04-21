#include "sensor.h"

Sensor::Sensor() {}

Sensor::Sensor(int id, int indicatorId)
    : _id(id), _indicatorId(indicatorId){}

int Sensor::indicatorId() const { return _indicatorId; }
int Sensor::id() const { return _id; }
