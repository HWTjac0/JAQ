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
        id: stationList
        anchors.fill: parent
        anchors.margins: 7
        height: parent.height
        width: parent.width
        interactive: false
        model: stationHandler.stationModel
        Connections {
            target: stationHandler
            function onStationChanged() {
                for(var i = 0; i < stationHandler.stationModel.rowCount(); ++i) {
                    if (stationHandler.stationModel.getId(i) === stationHandler.currentStationId) {
                        stationList.currentIndex = i;
                        break;
                    }
                }
            }
        }
        delegate: ItemDelegate {
            width: parent.width
            property bool isSelected: stationList.currentIndex === index

            background: Rectangle {
                radius: 6
                border {
                    width: 1
                    color: mouse.hovered ? "#d0d0d0" : "#e2e2e2"
                }
                color: isSelected ? "#e3f2fd" : (mouse.hovered ? "#f8f8f8" : "white")

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 1
                    radius: parent.radius - 1
                    color: "transparent"
                }
            }

            contentItem: Text {
                text: stationAddress
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
                stationHandler.stationSelected(stationId)
                stationList.currentIndex = index;
            }
        }
    }
    Connections {
        target: cityHandler
        function onCityChanged() {
            stationList.model = stationHandler.stationModel
            stationList.currentIndex = -1
        }
    }
    Text {
        anchors.centerIn: parent
        visible: stationList.count === 0
        text: "Wybierz miasto"
        font.pixelSize: 16
        color: "#838383"
    }
}