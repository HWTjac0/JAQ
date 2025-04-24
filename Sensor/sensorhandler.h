#ifndef SENSORHANDLER_H
#define SENSORHANDLER_H

#include <QObject>

class sensorHandler : public QObject
{
    Q_OBJECT
public:
    explicit sensorHandler(QObject *parent = nullptr);

signals:
};

#endif // SENSORHANDLER_H
