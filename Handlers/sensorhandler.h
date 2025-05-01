#ifndef SENSORHANDLER_H
#define SENSORHANDLER_H

#include <QObject>
#include "../core/apiclient.h"
#include "../Models/sensormodel.h"

class SensorHandler : public QObject
{
    // indicator and id are explicitly because sensor is not qobject
    Q_OBJECT
    Q_PROPERTY(SensorModel* sensorModel READ sensorModel CONSTANT);
    Q_PROPERTY(QString currentSensorIndicator READ currentSensorIndicator CONSTANT);
    Q_PROPERTY(int currentSensorId READ currentSensorId CONSTANT)
public:
    QString currentSensorIndicator() const;
    int currentSensorId() const;
    explicit SensorHandler(ApiClient* apiClient, QObject *parent = nullptr);
    Q_INVOKABLE SensorModel* sensorModel() const;
    void loadSensorsForStation();
public slots:
    void sensorSelected(int sensorId);
    void onCityChanged();
signals:
    void currentSensorChanged(Sensor *sensor);

private:
    ApiClient *_client;
    SensorModel *_sensorModel;
    Sensor _currentSensor;
};

#endif // SENSORHANDLER_H
