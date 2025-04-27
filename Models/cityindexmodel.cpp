#include "cityindexmodel.h"

CityIndexModel::CityIndexModel(QObject *parent)
    : QAbstractListModel(parent) {}

int CityIndexModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return _entries.count();
}

QHash<int, QByteArray> CityIndexModel::roleNames() const {
    return {
            {DisplayRole, "cityDisplay"},
            {IdRole, "cityId"},
            {CityNameRole, "cityName"},
            {VoivodeshipRole, "cityVoivodeship"}
        };
}

QVariant CityIndexModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= _entries.count())
        return QVariant();

    City *city = _entries.at(index.row());
    switch (role) {
        case DisplayRole: return QString("%1, %2").arg(city->name(), city->voivodeship());
        case CityNameRole: return city->name();
        case VoivodeshipRole:  return city->voivodeship();
        case IdRole: return city->id();
        default: return QVariant();
    }
}
void CityIndexModel::addCity(City *city)
{
    beginInsertRows(QModelIndex(), _entries.count(), _entries.count());
    _entries.append(city);
    endInsertRows();
}

void CityIndexModel::addCities(const QList<City*> &cities)
{
    if (cities.isEmpty())
        return;

    beginInsertRows(QModelIndex(), _entries.count(), _entries.count() + cities.count() - 1);
    _entries.append(cities);
    endInsertRows();
}

void CityIndexModel::clear()
{
    beginResetModel();
    _entries.clear();
    endResetModel();
}


QString CityIndexModel::getDisplayText(int index) const
{
    if (index >= 0 && index < _entries.count()) {
        City *city = _entries.at(index);
        return QString("%1, %2").arg(city->name(), city->voivodeship());
    }
    return QString();
}

int CityIndexModel::getId(int index) const
{
    if (index >= 0 && index < _entries.count())
        return _entries.at(index)->id();
    return -1;
}
