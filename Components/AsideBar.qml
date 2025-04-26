import QtQuick
import QtQuick.Layouts

Rectangle {
    Layout.preferredWidth: 240
    Layout.fillHeight: true
    Layout.leftMargin: 10
    Layout.bottomMargin: 10
    radius: 25
    topLeftRadius: 5
    topRightRadius: 5
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
                spacing: 10
                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Stacje dla miasta"
                    font.bold: true
                    font.pixelSize: 14
                    color: "#636b72"
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#f1f0f0"
                    radius: 15
                    border.width: 2
                    border.color: "#dddddd"
                }
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
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#f1f0f0"
                    radius: 15
                    border.width: 2
                    border.color: "#dddddd"
                }
            }
        }
    }
}