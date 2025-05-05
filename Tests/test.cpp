#include <QCoreApplication> // Include if your tested code needs an event loop or app instance
#include <QObject>
#include <QtTest/QtTest>
#include "../Handlers/SensorDataHandler.h"
#include "core/Database/databasereader.h"

class TestAirQuality : public QObject {
    Q_OBJECT
private slots:
    void initTestCase();
    void testParseIndicator();
    void testParseCity();
    void testParseSensors();
    void testParseStation();
    void testCityToIndexEntry();
    void testStationToIndexEntry();
private:
    DatabaseReader testReader;
};

void TestAirQuality::initTestCase() {
    qDebug() << "Starting test suite...";
}
void TestAirQuality::testParseIndicator() {
    QJsonObject indiObj;
    indiObj["name"] = "name";
    indiObj["code"] = "code";
    Indicator ind = testReader.parseIndicator(indiObj);

    QVERIFY(ind.code == "name");
    QVERIFY(ind.name == "code");
}
void TestAirQuality::testParseCity() {
    QJsonObject cityObj;
    cityObj["name"] = "name";
    cityObj["voivodeship"] = "voivodeship";
    cityObj["county"] = "county";
    cityObj["commune"] = "commune";
    int cityId = 15;
    City* city = testReader.parseCity(cityObj, cityId);

    QVERIFY(city->name() == "name");
    QVERIFY(city->voivodeship() == "voivodeship");
    QVERIFY(city->county() == "county");
    QVERIFY(city->commune() == "commune");
    QVERIFY(city->id() == cityId);
    delete city;
}
void TestAirQuality::testParseSensors() {
    QJsonArray sensorsArr;
    QJsonObject sensObj;
    sensObj["id"] = "25";
    sensObj["indicator_id"] = "25";
    sensorsArr.append(sensObj);
    Sensor& sensor = testReader.parseSensors(sensorsArr).first();
    QVERIFY(sensor.id() == 25);
    QVERIFY(sensor.indicatorId() == 25);
}
void TestAirQuality::testParseStation() {
    QJsonObject stationObj;
    stationObj["address"] = "address";
    stationObj["id"] = "25";
    Station station = testReader.parseStation(stationObj);
    QVERIFY(station.id() == 25);
    QVERIFY(station.address() == "address");
}
void TestAirQuality::testCityToIndexEntry() {
    City city("name", "voivodeship", "county", "commune", 25);
    QJsonObject cityObj = city.toIndexEntry();
    QVERIFY(cityObj["id"] == 25);
    QVERIFY(cityObj["name"] == "name");
    QVERIFY(cityObj["voivodeship"] == "voivodeship");
    QVERIFY(cityObj["county"] == "county");
    QVERIFY(cityObj["commune"] == "commune");
}
void TestAirQuality::testStationToIndexEntry() {
    Station station(25, "address");
    QJsonObject stationObj = station.toIndexEntry();
    QVERIFY(stationObj["id"] == 25);
    QVERIFY(stationObj["name"] == "name");
}
QTEST_MAIN(TestAirQuality)

#include "test.moc"