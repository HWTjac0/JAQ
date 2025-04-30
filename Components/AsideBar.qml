import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Rectangle {
    Layout.preferredWidth: 240
    Layout.fillHeight: true
    Layout.leftMargin: 0
    Layout.bottomMargin: 0
    radius: 25
    topLeftRadius: 0
    topRightRadius: 0
    bottomLeftRadius: 0
    border.width: 1
    border.color: "#bdbdbd"
    color: "#d6e6fa"
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 15
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#eef7ff"
            border.color: "#cdcdcd"
            border.width: 1
            radius: 20
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 8
                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Stacje dla miasta"
                    font.bold: true
                    font.pixelSize: 14
                    color: "#636b72"
                }
                Rectangle {
                    height: 2
                    width: 100
                    Layout.alignment: Qt.AlignHCenter
                    color: "#b8ccd2"
                }
                StationSelectList {}
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#eef7ff"
            border.color: "#cdcdcd"
            border.width: 1
            radius: 20
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 10
                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Stanowiska dla stacji"
                    wrapMode: Text.WordWrap
                    font.bold: true
                    font.pixelSize: 14
                    color: "#636b72"
                }
                Rectangle {
                    height: 2
                    width: 100
                    Layout.alignment: Qt.AlignHCenter
                    color: "#b8ccd2"
                }
                SensorSelectList {}
            }
        }
    }
}