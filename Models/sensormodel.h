#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "../Entities/sensor.h"

class SensorModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        IndicatorRole,
        DisplayRole
    };
    explicit SensorModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void clear();
    void setSensors(const QList<Sensor> &sensors);
private:
    QList<Sensor> _sensors;
};

#endif // SENSORMODEL_H
