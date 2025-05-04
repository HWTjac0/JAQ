import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: root
    property string address: "Adres stacji: <wybierz stacje z listy>"
    property string stationId: "ID stacji: <po wybraniu stacji>"
    property string aqiStatus: "Indeksy jakości wskaźników - <po wybraniu stacji>"

    Column {
        anchors.top: root.top
        spacing: 5

        Text {
            text: root.address
            font {
                pixelSize: 17
                bold: true
            }
        }
        Text {
            text: root.stationId
            font.pixelSize: 15
        }
        Text {
            id: aqiPlaceholder
            visible: true
            text: aqiStatus
        }
        ListModel {
            id: aqiStatusModel
        }
        Connections {
            target: cityHandler
            function onCityChanged() {
                aqiRows.visible = false;
                aqiPlaceholder.visible = true;
            }
        }
        Connections {
            target: stationHandler
            function onStationAQIAcquired(aqiData) {
                aqiRows.visible = true
                aqiPlaceholder.visible = false
                aqiStatusModel.clear()
                for(var key in aqiData) {
                    aqiStatusModel.append({
                        indicator: key,
                        value: aqiData[key]
                    })
                }
            }
        }
        ColumnLayout {
            id: aqiRows
            spacing: 5
            Repeater {
                model: aqiStatusModel
                delegate: Row {
                    spacing: 10
                    Label {
                        text: (indicator == "summary" ? "Ogólny stan powietrza" : `Indeks dla wskaźnika ${indicator}`) + ":"
                        font.pixelSize: 15
                    }
                    Text {
                        text: value.toString() ? value.toString() : "Brak indeksu"
                        font.pixelSize: 15
                    }
                }
            }
        }
    }
}