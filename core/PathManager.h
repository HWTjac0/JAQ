//
// Created by jac on 5/3/25.
//

#ifndef PATHMANAGER_H
#define PATHMANAGER_H
#include <QObject>

class PathManager : public QObject {
    Q_OBJECT
public:
    static QString baseDataDirectory();
    static QString cityIndex();
    static QString indicatorIndex();
    static QString sensorDataDirectory(int stationId, int sensorId);

    static bool doesPathExist(const QString &path);
    static bool doesFileExist(const QString &path);

private:
    static QString buildPath(const QString &path);
};



#endif //PATHMANAGER_H
