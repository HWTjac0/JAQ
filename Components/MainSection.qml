import QtQuick
import QtQuick.Layouts

Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.leftMargin: 20
    Layout.topMargin: 17
    topLeftRadius: 50
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 5
        Item {
            Layout.fillWidth: true
            Text {
                id: mainCityName
                text: "Miasto: <wybierz z listy>"
                font {
                    pixelSize: 30
                    bold: true
                }
            }
            Text {
                anchors.top: mainCityName.bottom
                anchors.margins: 5
                id: mainStationName
                text: "Stacja: <wybierz z listy>"
                font {
                    pixelSize: 20
                    bold: true
                }
            }
        }
        Connections {
            target: cityHandler
            function onCityChanged() {
                var title = "Miasto: %1"
                mainCityName.text = title.arg(cityHandler.currentCityName)
                mainStationName.text = "Stacja: <wybierz z listy>"
            }
        }
        Connections {
            target: stationHandler
            function onStationChanged() {
                var title = "Stacja: %1"
                mainStationName.text = title.arg(stationHandler.currentStationName)
            }
        }
    }
}