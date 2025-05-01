import QtQuick
import QtQuick.Layouts

Item {
    id: root
    property string indicator: "Wskaźnik stanowiska: <wybierz stanowisko z listy>"
    property string sensorId: "ID stanowiska: <po wybraniu stanowiska>"
    Layout.fillWidth: true
    Layout.preferredHeight: childrenRect.height
    Column {
        anchors.top: root.top
        spacing: 5

        Text {
            text: root.indicator
            font {
                pixelSize: 17
                bold: true
            }
        }
        Text {
            text: root.sensorId
            font.pixelSize: 15
        }
    }
}