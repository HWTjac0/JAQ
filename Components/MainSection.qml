import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

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
        CityInfo {
            id: cityInfo
        }
        DividerHorizontal {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: parent.width * 0.8
        }
        StationInfo {
            id: stationInfo
        }
        SensorDataTable {
            id: sensorDataTable
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: sensorDataHandler.sensordataModel
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
            }
        }
        Connections {
            target: stationHandler
            function onStationChanged() {
                stationInfo.address     = `Adres stacji: ${stationHandler.currentStationAddress}`
                stationInfo.stationId   = `ID stacji: ${stationHandler.currentStationId}`
                stationInfo.aqiStatus   = "Ogólny stan powietrza: Ładowanie..."
            }
            function  onStationAQIAcquired(aqiStatus) {
                try {
                    stationInfo.aqiStatus  = `Ogólny stan powietrza: ${aqiStatus}`
                } catch(e) {
                    console.error("Error updating AQI:", e)
                }
            }
        }
    }
}