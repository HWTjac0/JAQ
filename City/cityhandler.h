#ifndef CITYHANDLER_H
#define CITYHANDLER_H
#include <QDebug>
#include <QObject>
#include "../core/apiclient.h"
#include "cityindexmodel.h"
#include "citysortproxymodel.h"

class CityHandler : public QObject
{
    Q_OBJECT
public:
    CityHandler(ApiClient *client, QObject *parent = nullptr);
    Q_INVOKABLE CitySortProxyModel* getCities() const;
    Q_SIGNAL void cityChanged(const QString &city_name);
    Q_INVOKABLE int getCityId(int comboBoxIndex);
    Q_INVOKABLE void getCityStations(int comboBoxIndex);
public slots:
    void receiveText(const QString &text);
private:
    ApiClient *_client;
    CityIndexModel  *_baseModel;
    CitySortProxyModel *_proxyModel;
};

#endif // CITYHANDLER_H
