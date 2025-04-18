#ifndef APP_H
#define APP_H
#include <QGuiApplication>
#include <QQmlApplicationEngine>
class App
{
public:
    App();
    int init(int argc, char *argv[]);
};

#endif // APP_H
