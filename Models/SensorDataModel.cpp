//
// Created by jac on 5/1/25.
//

#include "SensorDataModel.h"


SensorDataModel::SensorDataModel(QObject *parent) : QAbstractTableModel(parent){
    _minValue = 0;
    _maxValue = 0;
    _timerangeStart = QDateTime::currentDateTime();
    _timerangeEnd = QDateTime::currentDateTime();
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

    _timerangeStart = _data.back().first;
    _timerangeEnd = _data.front().first;
    auto mm = std::minmax_element(_data.begin(), _data.end(), [](const QPair<QDateTime, double> &a, const QPair<QDateTime, double> &b) {
        return a.second < b.second;
    });
    _minValue = (*mm.first).second;
    _maxValue = (*mm.second).second;

    endResetModel();
}

void SensorDataModel::clear() {
    beginResetModel();
    _data.clear();
    endResetModel();
}

double SensorDataModel::minValue() const {
    return _minValue;
}

double SensorDataModel::maxValue() const {
    return _maxValue;
}

QDateTime SensorDataModel::timerangeStart() const {
    return _timerangeStart;
}

QDateTime SensorDataModel::timerangeEnd() const {
    return _timerangeEnd;
}

void SensorDataModel::fillSeries(QLineSeries *series) {
    series->clear();
    for (const auto& [timestamp, value] : _data) {
        series->append(timestamp.toMSecsSinceEpoch(), value);
    }
}


