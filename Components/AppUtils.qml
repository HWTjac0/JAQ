import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    anchors.fill: parent
    anchors.margins: 2
    spacing: 3
    Text {
        Layout.leftMargin: 15
        text: "Aplikacja"
        font.bold: true
        font.pixelSize: 12
        color: "#636b72"
    }
    Rectangle {
        Layout.fillWidth: true
        Layout.fillHeight: true
        color: "#fcfcfc"
        radius: 15
        border.width: 2
        border.color: "#dddddd"
        GridLayout {
            anchors.fill: parent
            anchors.margins: 7
            anchors.leftMargin: 15
            anchors.rightMargin: 15
            columns: 2
            rows: 2
            rowSpacing: 2
            Row {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Label {
                    id: connectionStatus
                    text: "Status połączenia: "
                    font {
                        pixelSize: 13
                    }
                }
                Text {
                    text: networkChecker.isOnline ? "Online" : "Offline"
                    color: networkChecker.isOnline ? "green" : "red"
                    font {
                        pixelSize: 13
                        bold: true
                    }
                }
            }
            Button {
                text: "Otwórz lokalną bazę danych"
                onClicked: database.openDatabase()
            }
        }
    }
}