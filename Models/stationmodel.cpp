#include "stationmodel.h"

StationModel::StationModel(QObject *parent) : QAbstractListModel(parent) {}

int StationModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : _stations.size();
}

QVariant StationModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() or index.row() >= _stations.size())
        return QVariant();

    const Station& station = _stations.at(index.row());
    switch (role) {
        case IdRole: return station.id();
        case AddressRole: return station.address();
        default: return QVariant();
    }
}

QHash<int, QByteArray> StationModel::roleNames() const {
    return {
        {IdRole, "stationId"},
        {AddressRole, "stationAddress"}
    };
}

int StationModel::getId(int i) {
    return _stations.at(i).id();
}

void StationModel::setStations(const QList<Station>& stations) {
    beginResetModel();
    _stations = stations;
    endResetModel();
}

void StationModel::clear() {
    beginResetModel();
    _stations.clear();
    endResetModel();
}
