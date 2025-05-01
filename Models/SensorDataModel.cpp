//
// Created by jac on 5/1/25.
//

#include "SensorDataModel.h"


SensorDataModel::SensorDataModel(QObject *parent) : QAbstractTableModel(parent){
}

int SensorDataModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return _data.size();
}

int SensorDataModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return 2;
}

QVariant SensorDataModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= _data.size())
        return {};

    const auto &entry = _data.at(index.row());
    const QDateTime &timestamp = entry.first;
    const double value = entry.second;

    switch (role) {
        case TimeStampRole:
            return timestamp;
        case ValueRole:
            return value;
        default:
            return {};
    }
}

QVariant SensorDataModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Horizontal) {
        return section == 0 ? tr("Timestamp") : tr("Value");
    }

    return QVariant();
}

QHash<int, QByteArray> SensorDataModel::roleNames() const {
    return {
        {TimeStampRole, "sensordataTimestamp"},
        {ValueRole, "sensordataValue"},
    };
}

void SensorDataModel::setData(const QVector<QPair<QDateTime, double>> &data) {
    beginResetModel();
    _data = data;
    endResetModel();
}

void SensorDataModel::clear() {
    beginResetModel();
    _data.clear();
    endResetModel();
}


