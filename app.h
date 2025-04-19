#ifndef APP_H
#define APP_H
#include <QGuiApplication>
#include <QQmlApplicationEngine>
class App : public QObject
{
    Q_OBJECT
public:
    App();
    int init(int argc, char *argv[]);
};

#endif // APP_H
