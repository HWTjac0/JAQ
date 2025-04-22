#ifndef DATABASE_H
#define DATABASE_H
#include "../apiclient.h"
#include "databasewriter.h"
#include "../../Sensor/sensor.h"
#include <QFile>
#include <QJsonDocument>
#include <QMutex>

class Database : public QObject
{
    Q_OBJECT
public:
    static QMap<int, City*> index;
    static QMap<int, Indicator> indicatorIndex;
    static QMutex indicatorMutex;
    Database() = default;
    Database(ApiClient *client, QObject* parent = nullptr);
    static City* getCity(int city_id);
public slots:
    void init();
signals:
    void dbPopulated();
private:
    QString _indexPath;
    DatabaseWriter* _writer;
    ApiClient *_client;
};

#endif // DATABASE_H
