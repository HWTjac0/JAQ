//
// Created by jac on 5/2/25.
//

#ifndef STATIONCOORDINATEMODEL_H
#define STATIONCOORDINATEMODEL_H
#include <QAbstractItemModel>
#include <QGeoCoordinate>

class StationCoordinateModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum Roles {
        CoordinateRole = Qt::UserRole + 1,
        IsActiveRole
    };

    explicit StationCoordinateModel(QObject *parent = nullptr);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addMarker(const QGeoCoordinate &coord, bool isActive = false);
    void updateMarker(int index, const QGeoCoordinate &coord, bool isActive = false);
    void setActiveMarker(int index);
    void clear();

private:
    struct MarkerData {
        QGeoCoordinate coordinate;
        bool isActive;
    };

    QList<MarkerData> _markers;
    int _activeIndex = -1;
};



#endif //STATIONCOORDINATEMODEL_H
