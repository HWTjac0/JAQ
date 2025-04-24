#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QObject>

class SensorModel : public QObject
{
    Q_OBJECT
public:
    explicit SensorModel(QObject *parent = nullptr);

signals:
};

#endif // SENSORMODEL_H
