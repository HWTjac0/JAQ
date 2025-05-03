//
// Created by jac on 5/3/25.
//

#include "NetworkChecker.h"

#include <QNetworkReply>

NetworkChecker::NetworkChecker(QObject *parent) : QObject(parent) {
    _manager = new QNetworkAccessManager(this);
    _timer = new QTimer(this);
    this->moveToThread(&_thread);
    _manager->moveToThread(&_thread);
    _timer->moveToThread(&_thread);

    _isOnline = false;
    connect(_timer, &QTimer::timeout, this, &NetworkChecker::checkConnection);
    connect(_manager, &QNetworkAccessManager::finished, this, &NetworkChecker::onReplyFinished);
    _thread.start();
}

NetworkChecker::~NetworkChecker() {
    _thread.quit();
    _thread.wait();
}

bool NetworkChecker::isOnline() const{
    return _isOnline;
}

void NetworkChecker::startChecking(int interval) {
    QMetaObject::invokeMethod(_timer, [this, interval]() {
       _timer->start(interval);
        checkConnection();
    });
}

void NetworkChecker::checkConnection() {
    if (_isChecking) return;

    _isChecking = true;
    QNetworkRequest req(QUrl("http://www.google.com"));
    QTimer::singleShot(3000, this, [this]() {
        if (_isChecking) {
            _isChecking = false;
            if (_isOnline) {
                _isOnline = false;
                emit connectionStatusChanged(true);
            }
        }
    });
    _manager->get(req);
}

void NetworkChecker::onReplyFinished(QNetworkReply *reply) {
    _isChecking = false;
    bool wasOnline = _isOnline;
    _isOnline = (reply->error() == QNetworkReply::NoError);
    if (wasOnline != _isOnline) {
        emit connectionStatusChanged(_isOnline);
    }
    reply->deleteLater();
}



