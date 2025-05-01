//
// Created by jac on 5/1/25.
//

#ifndef SENSORDATAMODEL_H
#define SENSORDATAMODEL_H
#include <qabstractitemmodel.h>
#include <QObject>
#include <QPair>
#include <QVector>
#include <QDateTime>

class SensorDataModel : public QAbstractTableModel {
    Q_OBJECT
public:
    enum Roles {
        TimeStampRole = Qt::UserRole + 1,
        ValueRole,
    };
    explicit SensorDataModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setData(const QVector<QPair<QDateTime, double>> &data);
    void clear();
private:
    QVector<QPair<QDateTime, double>> _data;
};



#endif //SENSORDATAMODEL_H
