#include "databasewriter.h"
#include <QTextStream>
#include <QFile>
#include "database.h"
#include "core/PathManager.h"


DatabaseWriter::DatabaseWriter(QObject *parent, ApiClient *client, QString rootPath)
    : QObject{parent}
{
    _apiClient = client;
    _rootPath = rootPath;

    connect(this, &DatabaseWriter::allStationsProcessed, this, &DatabaseWriter::saveCompleteDatabase);
    connect(_apiClient, &ApiClient::sensorsFinished, this, &DatabaseWriter::handleFetchedSensors);
    connect(_apiClient, &ApiClient::stationsFinished, this, &DatabaseWriter::handleFetchedStations);
}

void DatabaseWriter::fetchAllData(){
    _apiClient->fetchStations();
}
void DatabaseWriter::processNextStation() {
    if(_pendingStationsQueue.isEmpty() and _isProcessingStations) {
        _isProcessingStations = false;
        emit allStationsProcessed();
    } else {
        _currentStation = _pendingStationsQueue.dequeue();
        _apiClient->fetchSensors(_currentStation.id());
    }
}
void DatabaseWriter::handleFetchedStations(QMap<int, City*> cities) {
    qDebug() << "Processing cities";
    _processingCities = cities;
    for(auto city : std::as_const(cities)) {
        for(auto& station : city->getStations()) {
            station.cityId = city->id();
            _pendingStationsQueue.enqueue(station);
        }
    }
    if(!_pendingStationsQueue.isEmpty()) {
        _isProcessingStations = true;
        processNextStation();
    }
}

void DatabaseWriter::handleFetchedSensors(
    QVector<Sensor> sensors,
    QVector<QPair<int, Indicator> > indicators
    ) {
    for(const auto& pair : indicators) {
        Database::indicatorIndex.insert(pair.first, pair.second);
    }
    _processingCities.value(_currentStation.cityId)->setStationsSensors(_currentStation.id(), sensors);
    if(_isProcessingStations) {
        processNextStation();
    }
}
QJsonObject DatabaseWriter::serializeCities(QMap<int, City*> cities) {
    QJsonObject index_obj;
    for(auto city = cities.cbegin(); city != cities.cend(); city++) {
        index_obj.insert(QString::number(city.value()->id()), city.value()->toIndexEntry());
    }
    return index_obj;
}

QJsonObject DatabaseWriter::serializeIndicators(QMap<int, Indicator> indicators){
    QJsonObject obj;
    for(const auto [key, value] : indicators.asKeyValueRange()) {
        QJsonObject indicator;
        indicator.insert("name", value.name);
        indicator.insert("code", value.code);
        obj.insert(QString::number(key), indicator);
    }
    return obj;
}

void DatabaseWriter::saveSensorData(const QVector<QPair<QString, double>> &data, const QString &date, const QString &path) {
    QString buffer;
    QTextStream stream(&buffer);
    for (const auto &value : data) {
        stream << value.first << ";" << QString::number(value.second) << "\n";
    }
    QString filePath = path + date;// It has trailing '/' character
    QFile file(filePath);
    try {
        file.open(QIODevice::WriteOnly);
        qint64 bytes_written = file.write(buffer.toStdString().c_str());
        if (bytes_written == -1) {
            throw std::runtime_error("Error writing to file");
        }
        file.close();
    } catch (std::exception &e) {
        qWarning() << e.what();
    }
}


void DatabaseWriter::saveCompleteDatabase() {
    QJsonObject cityIndex = serializeCities(_processingCities);
    QJsonObject indicatorIndex = serializeIndicators(Database::indicatorIndex);

    writeJson(cityIndex, PathManager::cityIndex());
    writeJson(indicatorIndex, PathManager::indicatorIndex());
    qDebug() << "Indexes written!";
    emit indexesReady();
}

// write relative to root path
void DatabaseWriter::writeJson(const QJsonObject &json, const QString &path) {
    QFile file(path);
    PathManager::doesPathExist(PathManager::baseDataDirectory());
    try {
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QJsonDocument doc(json);
        qint64 bytes_written = file.write(doc.toJson());
        if(bytes_written == -1) {
            throw std::runtime_error("Failed to write index database");
        }
        file.close();
    } catch (std::exception &e) {
        qWarning() << "Error: " << e.what();
    } catch (...) {
        qWarning() << "Error writing index database";
    }
}
