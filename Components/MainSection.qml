import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtCharts


Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.leftMargin: 20
    Layout.topMargin: 17
    topLeftRadius: 50
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20
        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 10
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 20
                    CityInfo {
                        id: cityInfo
                        Layout.alignment: Qt.AlignVCenter
                        Layout.fillWidth: true
                        Layout.preferredHeight: 120
                    }
                    DividerHorizontal {
                        Layout.alignment: Qt.AlignHCenter
                        Layout.preferredWidth: parent.width * 0.8
                    }
                    StationInfo {
                        id: stationInfo
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.preferredHeight: 40
                    }
                }
            }
            MapView { id: map}
        }
        DividerHorizontal {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: parent.width * 0.8
        }
        SensorInfo {
            id: sensorInfo
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            RowLayout {
                anchors.fill: parent
                SensorDataTableView {}
                SensorDataChart {}
            }
        }

        Connections {
            target: cityHandler
            function onCityChanged() {

                cityInfo.cityName           = `Miasto: ${cityHandler.currentCity.name}`
                cityInfo.voivodeship        = `Województwo: ${cityHandler.currentCity.voivodeship}`
                cityInfo.county             = `Powiat: ${cityHandler.currentCity.county}`
                cityInfo.commune            = `Gmina: ${cityHandler.currentCity.commune}`

                stationInfo.address         = "Adres stacji: <wybierz stacje z listy>"
                stationInfo.stationId       = "ID stacji: <po wybraniu stacji>"
                stationInfo.aqiStatus       = "Ogólny stan powietrza: <po wybraniu stacji>"

                sensorInfo.indicator        = "Wskaźnik stanowiska: <wybierz stanowisko z listy>"
                sensorInfo.sensorId         = "ID stanowiska: <po wybraniu stanowiska>"            }
        }
        Connections {
            target: stationHandler
            function onStationChanged() {
                stationInfo.address     = `Adres stacji: ${stationHandler.currentStationAddress}`
                stationInfo.stationId   = `ID stacji: ${stationHandler.currentStationId}`
                stationInfo.aqiStatus   = "Ogólny stan powietrza: Ładowanie..."

                sensorInfo.indicator        = "Wskaźnik stanowiska: <wybierz stanowisko z listy>"
                sensorInfo.sensorId         = "ID stanowiska: <po wybraniu stanowiska>"
            }
            function  onStationAQIAcquired(aqiStatus) {
                try {
                    stationInfo.aqiStatus  = `Ogólny stan powietrza: ${aqiStatus}`
                } catch(e) {
                    console.error("Error updating AQI:", e)
                }
            }
        }
        Connections {
            target: sensorHandler
            function onCurrentSensorChanged(sensor) {
                sensorInfo.indicator        = `Wskaźnik stanowiska: ${sensorHandler.currentSensorIndicator}`
                sensorInfo.sensorId         = `ID stanowiska: ${sensorHandler.currentSensorId}`
            }
        }
    }
}