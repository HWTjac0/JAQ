#ifndef DATABASE_H
#define DATABASE_H
#include "apiclient.h"
#include <QFile>
#include <QJsonDocument>
class Database : public QObject
{
    Q_OBJECT
public:
    static QMap<int, City*> index;
    static QList<City*> cities;
    Database() = default;
    Database(ApiClient *client);
    void populate();
public slots:
    void init();
signals:
    void dbPopulated();
private:
    QString _indexPath;
    ApiClient *_client;
};

#endif // DATABASE_H
