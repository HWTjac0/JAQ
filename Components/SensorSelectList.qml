import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: "#f1f0f0"
    radius: 15
    border.width: 2
    border.color: "#dddddd"
    ListView {
        id: sensorsList
        anchors.fill: parent
        anchors.margins: 7
        width: parent.width
        height: parent.height
        interactive: false
        model: sensorHandler.sensorModel
        delegate: ItemDelegate {
            width: parent.width

            background: Rectangle {
                radius: 6
                border {
                    width: 1
                    color: mouse.hovered ? "#d0d0d0" : "#e2e2e2"
                }
                color: mouse.hovered ? "#f8f8f8" : "white"

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 1
                    radius: parent.radius - 1
                    color: "transparent"
                }
            }

            contentItem: Text {
                text: sensorDisplay
                font.pixelSize: 14
                verticalAlignment: Text.AlignVCenter
                leftPadding: 5
                rightPadding: 5
                elide: Text.ElideRight
            }

            HoverHandler {
                id: mouse
                acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
                cursorShape: Qt.PointingHandCursor
            }

            onClicked: {
                sensorHandler.sensorSelected(sensorId)
            }
        }
    }
    Connections {
        target: stationHandler
        function onStationChanged() {
            sensorsList.model = sensorHandler.sensorModel
        }
    }
    Connections {
        target: cityHandler
        function onCityChanged() {
            sensorsList.model.clear()
        }
    }

    Text {
        anchors.centerIn: parent
        visible: sensorsList.count === 0
        text: "Wybierz stacje"
        font.pixelSize: 16
        color: "#838383"
    }
}