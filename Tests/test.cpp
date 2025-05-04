#include <QCoreApplication> // Include if your tested code needs an event loop or app instance
#include <QObject>
#include <QtTest/QtTest>
#include "../Handlers/SensorDataHandler.h"
class TestAirQuality : public QObject {
    Q_OBJECT
private slots:
    void initTestCase();
    void testParseIndicator();
    void testParseCity();
    void testParseSensors();
    void testCityToIndexEntry();
    void testStationToIndexEntry();
};

void TestAirQuality::initTestCase() {
    qDebug() << "Starting test suite...";
}
void TestAirQuality::testParseIndicator() {}
void TestAirQuality::testParseCity() {}
void TestAirQuality::testParseSensors() {}
void TestAirQuality::testCityToIndexEntry() {}
void TestAirQuality::testStationToIndexEntry() {}
QTEST_MAIN(TestAirQuality)

#include "test.moc"