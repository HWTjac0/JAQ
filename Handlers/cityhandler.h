#ifndef CITYHANDLER_H
#define CITYHANDLER_H
#include <QDebug>
#include <QObject>
#include "../core/apiclient.h"
#include "../Models/cityindexmodel.h"
#include "../Models/citysortproxymodel.h"
#include "stationhandler.h"

class CityHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentCityName READ currentCityName CONSTANT)
public:
    static City* currentCity;
    CityHandler(ApiClient *client, QObject *parent = nullptr);
    QString currentCityName();
    Q_INVOKABLE CitySortProxyModel* getCities() const;
    Q_INVOKABLE int getCityId(int comboBoxIndex) const;
    Q_INVOKABLE StationHandler* stationHandler() const;
public slots:
    void citySelected(int comboBoxIndex);
signals:
    void cityChanged();
private:
    ApiClient *_client;
    CityIndexModel  *_baseModel;
    CitySortProxyModel *_proxyModel;
    StationHandler *_stationHandler;
};

#endif // CITYHANDLER_H
