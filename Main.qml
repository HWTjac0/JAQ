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
            width: 220
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
                model: cityHandler.stationHandler().stationModel()
                delegate: ItemDelegate {
                    text: address
                    font.pixelSize: 14
                    width: parent.width
                    onClicked: cityHandler.stationHandler().getStationUrl(stationId)
                }
            }
        }
    }
}
