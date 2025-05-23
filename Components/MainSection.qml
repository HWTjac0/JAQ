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
                Rectangle {
                    id: sensorDataPlaceholder
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: 15
                    color: "#cfcfcf"
                    Text {
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "Wybierz odpowiednią stacje"
                        font.pixelSize: 29
                        font.bold: true
                        color: "#afafaf"
                    }
                }
                ColumnLayout {
                    id: sensorDataWrapper
                    visible: false
                    Layout.fillWidth: true
                    spacing: 15
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
                                spacing: 100
                                SensorDataTableView {
                                    Layout.alignment: Qt.AlignRight
                                }
                                ColumnLayout {
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    spacing: 15
                                    ColumnLayout {
                                        Layout.fillWidth: true
                                        Layout.fillHeight: true
                                        spacing: 5
                                        Label {
                                            id: saveLabel
                                            text: "Zapisz pobrane dane"
                                            font.pixelSize: 17
                                            font.bold: true
                                        }
                                        Button {
                                            text: "Zapisz"
                                            onClicked: sensorDataHandler.saveData()
                                        }
                                    }
                                    ColumnLayout {
                                        Layout.fillWidth: true
                                        Layout.fillHeight: true
                                        spacing: 12
                                        Label {
                                            id: saveArchiveLabel
                                            text: "Pobierz archiwalne dane"
                                            font.pixelSize: 17
                                            font.bold: true
                                        }
                                        Row {
                                            id: archiveBeginRangex
                                            Label {
                                                id: archiveBeginLabel
                                                text: "Od:"
                                                font.pixelSize: 15
                                            }
                                            DatePicker {
                                                id: archiveBegin
                                                anchors.left: archiveBeginLabel.right
                                                width: 200
                                            }
                                        }
                                        Row {
                                            id: archiveEndRange
                                            Label {
                                                id: archiveEndLabel
                                                text: "Do:"
                                                font.pixelSize: 15
                                            }
                                            DatePicker {
                                                id: archiveEnd
                                                anchors.left: archiveEndLabel.right
                                                width: 200
                                            }
                                        }
                                        Button {
                                            text: "Załaduj"
                                            font.pixelSize: 14
                                            onClicked: {
                                                sensorDataHandler.getArchiveData(archiveBegin.currentDate, archiveEnd.currentDate)
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        Item {
                            RowLayout {
                                anchors.fill: parent
                                ColumnLayout {
                                    Layout.fillHeight: true
                                    Layout.preferredWidth: childrenRect.width
                                    Row {
                                        spacing: 5
                                        Label {
                                            text: "Maksymalna wartość:"
                                            font {
                                                bold: true
                                                pixelSize: 15
                                            }
                                        }
                                        Text {
                                            id: maxValue
                                            font.pixelSize: 15
                                        }
                                    }
                                    Row {
                                        spacing: 5
                                        Label {
                                            text: "Minimalna wartość:"
                                            font {
                                                bold: true
                                                pixelSize: 15
                                            }
                                        }
                                        Text {
                                            id: minValue
                                            font.pixelSize: 15
                                        }
                                    }
                                    Row {
                                        spacing: 5
                                        Label {
                                            text: "Średnia:"
                                            font {
                                                bold: true
                                                pixelSize: 15
                                            }
                                        }
                                        Text {
                                            id: averageValue
                                            font.pixelSize: 15
                                        }
                                    }
                                    Row {
                                        spacing: 5
                                        Label {
                                            text: "Trend:"
                                            font {
                                                bold: true
                                                pixelSize: 15
                                            }
                                        }
                                        Text {
                                            id: trendValue
                                            font.pixelSize: 15
                                        }
                                    }
                                    Connections {
                                        target: sensorDataHandler

                                        function onDataChanged() {
                                            minValue.text = sensorDataModel.minValue.toFixed(2)
                                            maxValue.text = sensorDataModel.maxValue.toFixed(2)
                                            averageValue.text = sensorDataModel.average.toFixed(2)

                                            trendValue.text = sensorDataModel.trend
                                            trendValue.color = getTrendColor(sensorDataModel.trend)
                                        }

                                        function getTrendColor(trend) {
                                            if (trend === "Rosnący") {
                                                return "red"
                                            } else if (trend === "Malejący") {
                                                return "green"
                                            } else {
                                                return "black"
                                            }
                                        }
                                    }
                                }
                                SensorDataChart {
                                }
                            }
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
                stationInfo.aqiStatus       =  "Indeksy jakości wskaźników - <po wybraniu stacji>"

                sensorInfo.indicator        = "Wskaźnik stanowiska: <wybierz stanowisko z listy>"
                sensorInfo.sensorId         = "ID stanowiska: <po wybraniu stanowiska>"

                sensorDataWrapper.visible = false
                sensorDataPlaceholder.visible = true
            }
        }
        Connections {
            target: stationHandler
            function onStationChanged() {
                stationInfo.address     = `Adres stacji: ${stationHandler.currentStationAddress}`
                stationInfo.stationId   = `ID stacji: ${stationHandler.currentStationId}`
                stationInfo.aqiStatus   = "Indeksy jakości wskaźników - Ładowanie"
                sensorInfo.indicator        = "Wskaźnik stanowiska: <wybierz stanowisko z listy>"
                sensorInfo.sensorId         = "ID stanowiska: <po wybraniu stanowiska>"
                sensorDataWrapper.visible = false
                sensorDataPlaceholder.visible = true
            }
        }
        Connections {
            target: sensorHandler
            function onCurrentSensorChanged(sensor) {
                sensorInfo.indicator        = `Wskaźnik stanowiska: ${sensorHandler.currentSensorIndicator}`
                sensorInfo.sensorId         = `ID stanowiska: ${sensorHandler.currentSensorId}`

                sensorDataWrapper.visible = false
                sensorDataPlaceholder.visible = true
            }
        }
        Connections {
            target: sensorDataHandler
            function onDataChanged() {
                if(sensorDataModel.size) {
                    sensorDataWrapper.visible = true
                    sensorDataPlaceholder.visible = false
                } else {
                    sensorDataWrapper.visible = false
                    sensorDataPlaceholder.visible = true
                }
            }
        }
    }
}