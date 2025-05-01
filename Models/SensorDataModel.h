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
#include <QtCharts/QLineSeries>

class SensorDataModel : public QAbstractTableModel {
    Q_OBJECT
    Q_PROPERTY(QDateTime timerangeStart READ timerangeStart CONSTANT);
    Q_PROPERTY(QDateTime timerangeEnd  READ timerangeEnd CONSTANT);
    Q_PROPERTY(double minValue READ minValue CONSTANT)
    Q_PROPERTY(double maxValue READ maxValue CONSTANT)
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

    double minValue() const;
    double maxValue() const;
    QDateTime timerangeStart() const;
    QDateTime timerangeEnd() const;

    Q_INVOKABLE void fillSeries(QLineSeries *series);
signals:
    void dataChanged();
private:
    QVector<QPair<QDateTime, double>> _data;

    QDateTime _timerangeStart;
    QDateTime _timerangeEnd;
    double _minValue;
    double _maxValue;
};



#endif //SENSORDATAMODEL_H
