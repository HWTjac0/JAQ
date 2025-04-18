#ifndef CITYHANDLER_H
#define CITYHANDLER_H
#include <QDebug>
#include <QObject>
#include "apiclient.h"

class CityHandler : public QObject
{
    Q_OBJECT
public:
    CityHandler(ApiClient *client);
public slots:
    void receiveText(const QString &text);

private:
    ApiClient *_client;
};

#endif // CITYHANDLER_H
