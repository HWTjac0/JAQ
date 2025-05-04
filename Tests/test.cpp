#include <QCoreApplication> // Include if your tested code needs an event loop or app instance
#include <QObject>
#include <QtTest/QtTest>
#include "../Handlers/SensorDataHandler.h"
class TestAirQuality : public QObject {
    Q_OBJECT
private slots:
    void initTestCase();
    void testAppContextCreation();
};

void TestAirQuality::initTestCase() {
    qDebug() << "Starting test suite...";
}

void TestAirQuality::testAppContextCreation() {
    double sum = 25 + 3;
    QVERIFY(sum == 28);
}

QTEST_MAIN(TestAirQuality)

#include "test.moc"