#ifndef APP_H
#define APP_H
#include <QGuiApplication>
#include <QQmlApplicationEngine>
class App : public QObject
{
    Q_OBJECT
public:

    App();
    static App* instance();
    int init(int argc, char *argv[]);
    void initAppMetadata();
private:
    static App *_instance;

};

#endif // APP_H
