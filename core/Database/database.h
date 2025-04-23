#ifndef DATABASE_H
#define DATABASE_H
#include "../apiclient.h"
#include "databasewriter.h"
#include "databasereader.h"
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
    Database() = default;
    Database(ApiClient *client, QObject* parent = nullptr);
    static void addCity(int cityId, City *city);
    static void addIndicator(int indicatorId, Indicator indicator);
    static City* getCity(int city_id);
public slots:
    void init();
signals:
    void dbPopulated();
private:
    QString _indexPath;
    DatabaseWriter *_writer;
    DatabaseReader *_reader;
    ApiClient *_client;
};

#endif // DATABASE_H
