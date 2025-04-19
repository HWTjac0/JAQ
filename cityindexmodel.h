#ifndef CITYINDEXMODEL_H
#define CITYINDEXMODEL_H
#include <QAbstractListModel>
#include <QSortFilterProxyModel>

#include "city.h"

class CityIndexModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        DisplayRole = Qt::UserRole + 1,
        IdRole,
        CityNameRole,
        VoivodeshipRole
    };

    explicit CityIndexModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addCity(City *city);
    void addCities(const QList<City *> &cities);
    void clear();
    Q_INVOKABLE QString getDisplayText(int index) const;
    int getId(int index) const;

    void sortByVoivodeship();
private:
    QList<City *> _entries;
};


class CitySortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit CitySortProxyModel(QObject *parent = nullptr)
        : QSortFilterProxyModel(parent) {
        setSortRole(CityIndexModel::VoivodeshipRole);
        sort(0);
    }

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override {
        QString leftVoivodeship = sourceModel()->data(left, CityIndexModel::VoivodeshipRole).toString();
        QString rightVoivodeship = sourceModel()->data(right, CityIndexModel::VoivodeshipRole).toString();

        // First sort by voivodeship, then by city name
        if (leftVoivodeship == rightVoivodeship) {
            QString leftName = sourceModel()->data(left, CityIndexModel::CityNameRole).toString();
            QString rightName = sourceModel()->data(right, CityIndexModel::CityNameRole).toString();
            return leftName < rightName;
        }
        return leftVoivodeship < rightVoivodeship;
    }
};

#endif // CITYINDEXMODEL_H
