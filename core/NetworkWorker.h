//
// Created by jac on 5/4/25.
//

#ifndef NETWORKWORKER_H
#define NETWORKWORKER_H

#include <QObject>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>

class NetworkWorker : public QObject {
    Q_OBJECT

public:
    explicit NetworkWorker(QObject *parent = nullptr);
    ~NetworkWorker() override;
    void initialize();
signals:
    void checkCompleted(bool isOnline, QNetworkReply::NetworkError error = QNetworkReply::NoError);

public slots:
    void start(int interval);
    void stop();

private slots:
    void performCheck();
    void onReplyFinished(QNetworkReply *reply);
    void handleTimeout();

private:
    QNetworkAccessManager *_manager = nullptr;
    QTimer *_checkTimer = nullptr;
    QTimer *_requestTimeoutTimer = nullptr;
    bool _isChecking = false;
    QUrl _checkUrl = QUrl("https://www.google.com");
    int _requestTimeoutMs = 3000;
};


#endif //NETWORKWORKER_H
