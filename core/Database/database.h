#ifndef DATABASE_H
#define DATABASE_H
#include "../apiclient.h"
#include "databasewriter.h"
#include "databasereader.h"
#include "../../Entities/sensor.h"
#include <QFile>
#include <QMutex>

class Database : public QObject
{
    Q_OBJECT
public:
    static QMap<int, City*> index;
    static QMap<int, Indicator> indicatorIndex;
    Database() = default;
    Database(ApiClient* apiClient, QObject* parent = nullptr);
    void init();
    bool exists();
    static void addCity(int cityId, City *city);
    static void addIndicator(int indicatorId, Indicator indicator);
    static Indicator getIndicator(int indicatorId);
    static City* getCity(int city_id);
signals:
    void databaseReady();
private:
    QString _indexPath;
    DatabaseWriter *_writer;
    DatabaseReader *_reader;
    ApiClient *_client;
    QString _standardPath;
};

#endif // DATABASE_H
