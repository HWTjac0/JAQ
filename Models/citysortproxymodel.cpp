#include "citysortproxymodel.h"
#include "cityindexmodel.h"

CitySortProxyModel::CitySortProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent) {
    setSortRole(CityIndexModel::VoivodeshipRole);
    sort(0);
}

bool CitySortProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const {
    QString leftVoivodeship = sourceModel()->data(left, CityIndexModel::VoivodeshipRole).toString();
    QString rightVoivodeship = sourceModel()->data(right, CityIndexModel::VoivodeshipRole).toString();

    if (leftVoivodeship == rightVoivodeship) {
        QString leftName = sourceModel()->data(left, CityIndexModel::CityNameRole).toString();
        QString rightName = sourceModel()->data(right, CityIndexModel::CityNameRole).toString();
        return leftName < rightName;
    }
    return leftVoivodeship < rightVoivodeship;
}

bool CitySortProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const {
    bool containsName = true;
    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
    QString name = sourceModel()->data(index, CityIndexModel::CityNameRole).toString();
    QString voivodeship = sourceModel()->data(index, CityIndexModel::VoivodeshipRole).toString();
    if(_filterString.isEmpty()){
        containsName = true;
    } else {
        containsName = name.contains(_filterString, Qt::CaseInsensitive);
    }
    bool voivodeshipMatch = _filterVoivodeship == voivodeship;

    return voivodeshipMatch and containsName;
}

QString CitySortProxyModel::filterString() const { return _filterString; }
void CitySortProxyModel::setFilterString(const QString &filterString){
    if(_filterString != filterString) {
        _filterString = filterString;
        invalidateFilter();
        emit filterStringChanged();
    }
}

QString CitySortProxyModel::filterVoivodeship() const {
    return _filterVoivodeship;
}

void CitySortProxyModel::setFilterVoivodeship(const QString &filterVoivodeship) {
    _filterVoivodeship = filterVoivodeship;
    invalidateFilter();
    emit filterVoivodeshipChanged();
}

