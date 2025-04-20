import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "./Components"

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("JAirQuality")
    ColumnLayout {
        width: parent.width
        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.margins: 10
            spacing: 3
            Label {
                Layout.alignment: Qt.AlignHCenter
                text: "Wybierz miasto"
                font.pixelSize: 20
                font.bold: true
            }
            SearchCity {
                Layout.alignment: Qt.AlignHCenter
            }
            Button {
                Layout.alignment: Qt.AlignHCenter
                text: "Sprawdź"
            }
        }
    }
}
