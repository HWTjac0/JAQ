#ifndef SENSORHANDLER_H
#define SENSORHANDLER_H

#include <QObject>
#include "../core/apiclient.h"
#include "../Models/sensormodel.h"

class SensorHandler : public QObject
{
    Q_OBJECT
public:
    static Sensor currentSensor;
    explicit SensorHandler(QObject *parent = nullptr);
    Q_INVOKABLE SensorModel* sensorModel() const;
    void loadSensorsForStation();
public slots:
    void sensorSelected(int sensorId);
    void onCityChanged();
private:
    ApiClient *_client;
    SensorModel *_sensorModel;
};

#endif // SENSORHANDLER_H
