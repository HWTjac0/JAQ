#include "station.h"

void Station::setAQIStatus(QString &status) {
    aqi_status = status;
}

Station::Station(const int id) {
    this->id = id;
}
