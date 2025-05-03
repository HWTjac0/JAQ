import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtCharts

Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.leftMargin: 12
    Layout.topMargin: 12
    topLeftRadius: 50
    color: "#ececec"
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 15
        spacing: 10
        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 10
            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "#fafafa"
                border {
                    width: 1
                    color: "#aaaaaa"
                }
                radius: 20
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
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
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#fafafa"
            border {
                width: 1
                color: "#aaaaaa"
            }
            radius: 20
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 15
                SensorInfo {
                    id: sensorInfo
                }
                TabBar {
                    id: mainBar
                    Layout.preferredWidth: parent.width * 0.4
                    Layout.alignment: Qt.AlignHCenter
                    TabButton {
                        text: "Dane"
                        font.pixelSize: 15
                        padding: 7
                    }
                    TabButton {
                        text: "Statystyki"
                        font.pixelSize: 15
                        padding: 7
                    }
                }
                StackLayout {
                    Layout.fillWidth: true
                    currentIndex: mainBar.currentIndex
                    Item {
                        RowLayout {
                            anchors.fill: parent
                            SensorDataTableView {}
                            ColumnLayout {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                Item {
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    Label {
                                        id: saveLabel
                                        text: "Zapisz pobrane dane"
                                    }
                                    Button {
                                        anchors.top: saveLabel.bottom
                                        text: "Zapisz"
                                        onClicked: sensorDataHandler.saveData()
                                    }
                                }
                                Item {
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    Label {
                                        id: saveArchiveLabel
                                        text: "Pobierz archiwalne dane"
                                    }
                                    Row {
                                        id: archiveBeginRange
                                        anchors.top: saveArchiveLabel.bottom
                                        Label {
                                            text: "Od:"
                                        }
                                    }
                                    Row {
                                        id: archiveEndRange
                                        anchors.top: archiveBeginRange.bottom
                                        Label {
                                            text: "Do:"
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Item {
                        RowLayout {
                            anchors.fill: parent
                            SensorDataChart {}
                        }
                    }
                }
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