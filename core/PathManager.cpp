//
// Created by jac on 5/3/25.
//

#include "PathManager.h"

#include <QDir>
#include <qstandardpaths.h>

QString PathManager::baseDataDirectory() {
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
}

QString PathManager::cityIndex() {
    return buildPath("indexCities.json");
}
QString PathManager::indicatorIndex() {
    return buildPath("indexIndicators.json");
}

QString PathManager::sensorDataDirectory(int stationId, int sensorId) {
    QString sensor = QString("sensorData/%1/%2/").arg(QString::number(stationId), QString::number(sensorId));
    QString sensorPath = buildPath(sensor);
    if (!doesPathExist(sensorPath)) {
        return baseDataDirectory();
    }
    return sensorPath;
}

QString PathManager::buildPath(const QString &path) {
    return QString("%1/%2")
    .arg(baseDataDirectory(), path);
}
bool PathManager::doesFileExist(const QString &path) {
    return QFile::exists(path);
}
bool PathManager::doesPathExist(const QString &path) {
    if (QDir dir(path); !dir.exists()) {
        return dir.mkpath(".");
    }
    return true;
}
