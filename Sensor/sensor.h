#ifndef SENSOR_H
#define SENSOR_H
#include <QString>

struct Indicator {
    QString code;
    QString name;
};

class Sensor
{
public:
    Sensor();
    Sensor(int id, int indicatorId);
    int id() const;
    int indicatorId() const;
private:
    int _id;
    int _indicatorId;
};

#endif // SENSOR_H
