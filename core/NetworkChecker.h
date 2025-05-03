//
// Created by jac on 5/3/25.
//

#ifndef NETWORKCHECKER_H
#define NETWORKCHECKER_H
#include <QNetworkAccessManager>
#include <QThread>
#include <QTimer>
#include <QObject>
#include "NetworkWorker.h"

class NetworkChecker : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool isOnline READ isOnline NOTIFY connectionStatusChanged);
public:
    explicit NetworkChecker(QObject *parent = nullptr);
    ~NetworkChecker();

    bool isOnline() const;
    void startChecking(int interval);
    void stopChecking();
signals:
    void initalizeWorkers();
    void connectionStatusChanged(bool isOnline);
    void operateWorker(int interval);
    void stopWorker();
private slots:
    void onWorkerCheckCompleted(bool isOnline, QNetworkReply::NetworkError error);
private:
    NetworkWorker* _networkWorker;
    QThread _thread;
    bool _isOnline;
};

#endif //NETWORKCHECKER_H
