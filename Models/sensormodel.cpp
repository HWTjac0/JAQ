#include "sensormodel.h"

SensorModel::SensorModel(QObject *parent)
    : QAbstractListModel{parent}
{}

int SensorModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : _sensors.size();
}

QVariant SensorModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid() or index.row() >= _sensors.size()) {
        return QVariant();
    }

    const Sensor& sensor = _sensors.at(index.row());
    const Indicator indicator = sensor.getIndicator();
    switch (role) {
            case IdRole: return sensor.id();
            case IndicatorRole: return indicator.code;
            case DisplayRole: return QString("%1 %2").arg(QString::number(sensor.id()), indicator.code);
            default: return QVariant();
    }

}

QHash<int, QByteArray> SensorModel::roleNames() const {
    return {
        {IdRole, "sensorId"},
        {IndicatorRole, "sensorIndicator"},
        {DisplayRole, "sensorDisplay"}
    };
}

void SensorModel::clear() {
    beginResetModel();
    _sensors.clear();
    endResetModel();
}

void SensorModel::setSensors(const QList<Sensor> &sensors) {
    beginResetModel();
    _sensors = sensors;
    for(auto s : _sensors) {
        qDebug() << s.getIndicator().code;
    }
    endResetModel();
}
