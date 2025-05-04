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
        return section == 0 ? tr("Data pomiaru") : tr("Wartość");
    }

    return QVariant();
}

QHash<int, QByteArray> SensorDataModel::roleNames() const {
    return {
        {Qt::DisplayRole, "display"},
        {TimeStampRole, "sensordataTimestamp"},
        {ValueRole, "sensordataValue"},
    };
}

// https://www.ncl.ac.uk/webtemplate/ask-assets/external/maths-resources/statistics/regression-and-correlation/simple-linear-regression.html
// https://en.wikipedia.org/wiki/Simple_linear_regression
QString SensorDataModel::calculateTrend(const QVector<QPair<QDateTime, double>> &data) {
    size_t n = static_cast<size_t>(data.size());

    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_xy = 0.0;
    double sum_xx = 0.0;

    for (size_t i = 0; i < n; ++i) {
        double xi = static_cast<double>(i);
        double yi = data[static_cast<int>(i)].second;

        sum_x += xi;
        sum_y += yi;
        sum_xy += xi * yi;
        sum_xx += xi * xi;
    }
    double numerator = (static_cast<double>(n) * sum_xy) - (sum_x * sum_y);
    double denominator = (static_cast<double>(n) * sum_xx) - (sum_x * sum_x);

    double slope = numerator / denominator;

    const double epsilon_slope = 1e-6; // tolerance for slope being flat
    if (slope > epsilon_slope) {
        return "Rosnący";
    } else if (slope < -epsilon_slope) {
        return "Malejący";
    } else {
        return "Stały";
    }
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

    double sum = 0;
    for (const auto& d : _data) {
        sum += d.second;
    }
    _average = sum / _data.size();
    _trend = calculateTrend(_data);
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

double SensorDataModel::average() const {
    return _average;
}

QString SensorDataModel::trend() const {
    return _trend;
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


