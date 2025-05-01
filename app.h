#ifndef APP_H
#define APP_H
#include <QGuiApplication>
#include <QQmlApplicationEngine>
class App : public QObject
{
    Q_OBJECT
public:
    App();
    static int init(int argc, char *argv[]);

    static void initAppMetadata();
};

#endif // APP_H
