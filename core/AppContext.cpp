//
// Created by jac on 5/1/25.
//

#include "AppContext.h"
#include "GeoLocator.h"
#include "Database/database.h"

AppContext* AppContext::_instance = nullptr;

AppContext* AppContext::getInstance() {
    if (_instance == nullptr) {
        _instance = new AppContext();
    }
    return _instance;
}

AppContext::AppContext(QObject *parent)
    : QObject(parent) {
}

void AppContext::initialize() {
    _networkChecker.reset(new NetworkChecker());
    connect(_networkChecker.get(), &NetworkChecker::connectionStatusChanged, this, &AppContext::networkStatusChanged, Qt::QueuedConnection);
    _networkChecker->startChecking(5000);
    _apiClient.reset(new ApiClient(this));
    _database.reset(new Database(_apiClient.get(), this));
    connect(_database.get(), &Database::databaseReady, this, [=]() {
        qDebug() << "AppContext::initialize";
        setupHandlers();
        emit initialized();
    });
    _database.get()->init();
}

void AppContext::setupHandlers() {
    /**
     * I am passing api client, handlers etc. explicitly because I think
     * implicit access to them is kind of convoluted for this init usage
     */
    _sensorHandler.reset(new SensorHandler(_apiClient.get(), this));
    _sensorDataHandler.reset(new SensorDataHandler(_apiClient.get(), this));
    _stationHandler.reset(new StationHandler(_apiClient.get(),_sensorHandler.get(),this));
    _cityHandler.reset(new CityHandler(_apiClient.get(), _stationHandler.get(), this));

    // Here will be connections between handlers
    connect(_cityHandler.get(),
        &CityHandler::cityChanged,
        _sensorHandler.get(),
        &SensorHandler::onCityChanged
        );
    connect(_sensorHandler.get(),
        &SensorHandler::currentSensorChanged,
        _sensorDataHandler.get(),
        &SensorDataHandler::onCurrentSensorChanged
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

SensorDataHandler* AppContext::getSensorDataHandler() const {
    return _sensorDataHandler.get();
}

ApiClient* AppContext::getApiClient() const {
    return _apiClient.get();
}

NetworkChecker * AppContext::getNetworkChecker() const {
    return _networkChecker.get();
}

bool AppContext::isOnline() const {
    return _networkChecker ? _networkChecker.get()->isOnline() : false;
}
