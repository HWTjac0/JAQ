//
// Created by jac on 5/3/25.
//

#ifndef NETWORKCHECKER_H
#define NETWORKCHECKER_H
#include <QNetworkAccessManager>
#include <QThread>
#include <QTimer>
#include <QObject>


class NetworkChecker : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool isOnline READ isOnline CONSTANT);
public:
    explicit NetworkChecker(QObject *parent = nullptr);
    ~NetworkChecker();

    bool isOnline() const;
public slots:
    void startChecking(int interval);
    void checkConnection();
    void onReplyFinished(QNetworkReply *reply);
signals:
    void connectionStatusChanged(bool isOnline);
private:
    QNetworkAccessManager *_manager;
    QTimer *_timer;
    QThread _thread;
    bool _isOnline;
    bool _isChecking;
};

#endif //NETWORKCHECKER_H
