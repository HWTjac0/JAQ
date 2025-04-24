#ifndef CITYHANDLER_H
#define CITYHANDLER_H
#include <QDebug>
#include <QObject>
#include "../core/apiclient.h"
#include "cityindexmodel.h"
#include "citysortproxymodel.h"
#include "../Station/stationhandler.h"

class CityHandler : public QObject
{
    Q_OBJECT
public:
    static City* currentCity;
    CityHandler(ApiClient *client, QObject *parent = nullptr);
    Q_INVOKABLE CitySortProxyModel* getCities() const;
    Q_INVOKABLE int getCityId(int comboBoxIndex);
    Q_SIGNAL void cityChanged(const QString &city_name);
    Q_INVOKABLE StationHandler* stationHandler() const;
public slots:
    void citySelected(int comboBoxIndex);
private:
    ApiClient *_client;
    CityIndexModel  *_baseModel;
    CitySortProxyModel *_proxyModel;
    StationHandler *_stationHandler;
};

#endif // CITYHANDLER_H
