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
        width: parent.width
        Column {
            width: 220
            ListView {
                width: parent.width
                height: 200
                interactive: false
                model: cityHandler.stationHandler().stationModel()
                delegate: ItemDelegate {
                    text: address
                    font.pixelSize: 15
                    width: parent.width
                    onClicked: cityHandler.stationHandler().getStationUrl(stationId)
                }
            }
        }
    }
}
