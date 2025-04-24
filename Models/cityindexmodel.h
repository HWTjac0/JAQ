#ifndef CITYINDEXMODEL_H
#define CITYINDEXMODEL_H
#include <QAbstractListModel>
#include <QSortFilterProxyModel>

#include "../Entities/city.h"

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

private:
    QList<City *> _entries;
};

#endif // CITYINDEXMODEL_H
