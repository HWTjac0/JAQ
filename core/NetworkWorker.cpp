//
// Created by jac on 5/4/25.
//

#include "NetworkWorker.h"
#include <QThread>

NetworkWorker::NetworkWorker(QObject *parent) : QObject(parent) {
    _isChecking = false;
}

NetworkWorker::~NetworkWorker() {
    if(_checkTimer) _checkTimer->stop();
    if(_requestTimeoutTimer) _requestTimeoutTimer->stop();

    delete _manager;
    delete _checkTimer;
    delete _requestTimeoutTimer;
}

void NetworkWorker::initialize() {
    _manager = new QNetworkAccessManager();
    _checkTimer = new QTimer();
    _requestTimeoutTimer = new QTimer();
    _requestTimeoutTimer->setSingleShot(true);

    connect(_checkTimer, &QTimer::timeout, this, &NetworkWorker::performCheck);
    connect(_manager, &QNetworkAccessManager::finished, this, &NetworkWorker::onReplyFinished);
    connect(_requestTimeoutTimer, &QTimer::timeout, this, &NetworkWorker::handleTimeout);
}

void NetworkWorker::start(int interval) {
    _checkTimer->start(interval);
    performCheck();
}

void NetworkWorker::stop() {
    _checkTimer->stop();
    _requestTimeoutTimer->stop();
    _isChecking = false;
}


void NetworkWorker::performCheck() {
    if (_isChecking) {
        return;
    }
    _isChecking = true;
    _requestTimeoutTimer->start(_requestTimeoutMs);

    QNetworkRequest req(_checkUrl);
    _manager->get(req);
}

void NetworkWorker::handleTimeout() {
    if (!_isChecking) return;

     _isChecking = false;
     emit checkCompleted(false, QNetworkReply::TimeoutError);
}

void NetworkWorker::onReplyFinished(QNetworkReply *reply) {
    _requestTimeoutTimer->stop();

    if (!_isChecking) {
        reply->deleteLater();
        return;
    }
    _isChecking = false;
    bool isOnline = (reply->error() == QNetworkReply::NoError);
    emit checkCompleted(isOnline, reply->error());
    reply->deleteLater();
}