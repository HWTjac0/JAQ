#ifndef STATIONMODEL_H
#define STATIONMODEL_H
#include <QObject>
#include <QAbstractListModel>
#include "../Entities/station.h"

class StationModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        AddressRole
    };

    explicit StationModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void clear();
    void setStations(const QList<Station> &stations);
    private:
    QList<Station> _stations;
};

#endif // STATIONMODEL_H
