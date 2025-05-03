//
// Created by jac on 5/3/25.
//

#include "NetworkChecker.h"

#include <QNetworkReply>

NetworkChecker::NetworkChecker(QObject *parent) : QObject(parent) {
    _isOnline = false;

    _networkWorker = new NetworkWorker();
    _networkWorker->moveToThread(&_thread);

    connect(_networkWorker, &NetworkWorker::checkCompleted, this, &NetworkChecker::onWorkerCheckCompleted, Qt::QueuedConnection);
    connect(this, &NetworkChecker::operateWorker, _networkWorker, &NetworkWorker::start, Qt::QueuedConnection);
    connect(this, &NetworkChecker::stopWorker, _networkWorker, &NetworkWorker::stop, Qt::QueuedConnection);
    connect(this, &NetworkChecker::initalizeWorkers, _networkWorker, &NetworkWorker::initialize, Qt::QueuedConnection);

    _thread.start();
    emit initalizeWorkers();
}

NetworkChecker::~NetworkChecker() {
    _thread.quit();
    _thread.wait();
}

bool NetworkChecker::isOnline() const{
    return _isOnline;
}

void NetworkChecker::startChecking(int interval) {
    emit operateWorker(5000);
}

void NetworkChecker::stopChecking() {
    emit stopWorker();
}

void NetworkChecker::onWorkerCheckCompleted(bool isOnline, QNetworkReply::NetworkError error) {
    if (_isOnline != isOnline) {
        _isOnline = isOnline;
        emit connectionStatusChanged(_isOnline);
    }
    Q_UNUSED(error);
}


