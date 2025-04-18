#ifndef DATABASE_H
#define DATABASE_H
#include "apiclient.h"
#include <QFile>
#include <QJsonDocument>
class Database : public QObject
{
    Q_OBJECT
public:
    Database() = default;
    Database(ApiClient *client);
    void init();

private:
    QString _indexPath;
    ApiClient *_client;
};

#endif // DATABASE_H
