import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "./Components"

Window {
    visible: true
    width: 600
    title: qsTr("JAirQuality")
    Rectangle {
        id: topBar
        width: parent.width
        height: 100
        color: "#5999cf"
        ColumnLayout {
            anchors.top: topBar.top
            anchors.left: topBar.left
            anchors.margins: 10
            Text {
                text: "Wybierz miasto którego stan powietrza chcesz sprawdzić"
                font.pixelSize: 20
                font.bold: true
                color: "white"
            }
            Row {
                SearchCity {}
            }
        }
    }
    Rectangle {
        anchors.top: topBar.bottom
        border.width: 2
        border.color: "black"
        width: parent.width
        Column {
            id: stationList
            width: 220
            height: 300
            Text {
                id: stationsTitle
                text: "Dostępne stacje pomiarowe"
                font.bold: true;
                font.pixelSize: 16
            }

            ListView {
                anchors.top: stationsTitle.bottom
                width: parent.width
                height: 200
                interactive: false
                model: stationHandler.stationModel()
                delegate: ItemDelegate {
                    text: address
                    font.pixelSize: 14
                    width: parent.width
                    onClicked: stationHandler.stationSelected(stationId)
                }
            }
        }
        Column {
            id: sensorList
            anchors.top: stationList.bottom
            width: 220
            Text {
                id: sensorsTitle
                text: "Dostępne stanowiska dla stacji"
                font.bold: true;
                font.pixelSize: 16
            }
            ListView {
                anchors.top: sensorsTitle.bottom
                width: parent.width
                height: 200
                interactive: false
                model: sensorHandler.sensorModel()
                delegate: ItemDelegate {
                    text: display
                    width: parent.width
                    font.pixelSize: 14
                }
            }
        }
    }
}
