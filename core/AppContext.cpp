//
// Created by jac on 5/1/25.
//

#include "AppContext.h"
#include "Database/database.h"
AppContext* AppContext::_instance = nullptr;

AppContext& AppContext::getInstance() {
    if (_instance == nullptr) {
        _instance = new AppContext();
    }
    return *_instance;
}

AppContext::AppContext(QObject *parent)
    : QObject(parent){}

void AppContext::initialize() {
    _apiClient.reset(new ApiClient(this));
    Database db(this);

    _sensorHandler.reset(new SensorHandler(this));
    _stationHandler.reset(new StationHandler(this));
    _cityHandler.reset(new CityHandler(this));

    connect(_cityHandler.get(),
        &CityHandler::cityChanged,
        _sensorHandler.get(),
        &SensorHandler::onCityChanged
        );
}


CityHandler* AppContext::getCityHandler() const{
    return _cityHandler.get();
}

StationHandler* AppContext::getStationHandler() const {
    return _stationHandler.get();
}

SensorHandler* AppContext::getSensorHandler() const {
    return _sensorHandler.get();
}

ApiClient* AppContext::getApiClient() const {
    return _apiClient.get();
}