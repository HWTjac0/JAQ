//
// Created by jac on 5/2/25.
//

#include "StationCoordinateModel.h"

StationCoordinateModel::StationCoordinateModel(QObject *parent) : QAbstractItemModel(parent) {}

QModelIndex StationCoordinateModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex StationCoordinateModel::parent(const QModelIndex &child) const {
    Q_UNUSED(child)
    return QModelIndex();
}

int StationCoordinateModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return _markers.count();
}

int StationCoordinateModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return 1;
}
QHash<int, QByteArray> StationCoordinateModel::roleNames() const {
    return {
        {CoordinateRole, "stationCoordinate"},
        {IdRole, "stationId"},
        {IsActiveRole, "stationCoordIsActive"}
    };
}

QVariant StationCoordinateModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= _markers.size())
        return QVariant();

    const MarkerData &marker = _markers.at(index.row());

    switch (role) {
        case IdRole:
            return marker.stationId;
        case CoordinateRole:
            return QVariant::fromValue(marker.coordinate);
        case IsActiveRole:
            return marker.isActive;
        case Qt::DisplayRole:
            return QString("(%1, %2)")
                .arg(marker.coordinate.latitude())
                .arg(marker.coordinate.longitude());
        default:
            return QVariant();
    }
}

void StationCoordinateModel::addMarker(const QGeoCoordinate &coord, int stationId, bool isActive) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _markers.append({stationId, coord, isActive});
    if (isActive) _activeIndex = rowCount();
    endInsertRows();
}

void StationCoordinateModel::updateMarker(int index, const QGeoCoordinate &coord, int stationId,  bool isActive) {
    if (index < 0 || index >= _markers.size())
        return;

    _markers[index] = {stationId, coord, isActive};
    if (isActive) _activeIndex = index;
    Q_EMIT dataChanged(this->index(index, 0), this->index(index, 0));
}

void StationCoordinateModel::setActiveMarker(int index) {
    if (index < -1 || index >= _markers.size())
        return;

    if (_activeIndex >= 0 && _activeIndex < _markers.size()) {
        _markers[_activeIndex].isActive = false;
        Q_EMIT dataChanged(this->index(_activeIndex, 0), this->index(_activeIndex, 0));
    }

    _activeIndex = index;
    if (_activeIndex >= 0) {
        _markers[_activeIndex].isActive = true;
        Q_EMIT dataChanged(this->index(_activeIndex, 0), this->index(_activeIndex, 0));
    }
}

void StationCoordinateModel::clear() {
    beginResetModel();
    _markers.clear();
    _activeIndex = -1;
    endResetModel();
}