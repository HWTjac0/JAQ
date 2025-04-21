#ifndef SENSOR_H
#define SENSOR_H
#include <QString>


class Sensor
{
public:
    Sensor();

private:
    int _id;
    QString _name;
    QString _code;
};

#endif // SENSOR_H
