import QtQuick
import QtQuick.Layouts

Item {
    id: root
    property string address: "Adres stacji: <wybierz stacje z listy>"
    property string stationId: "ID stacji: <po wybraniu stacji>"
    property string aqiStatus: "Ogólny stan powietrza: <po wybraniu stacji>"

    Column {
        anchors.top: root.top
        spacing: 5

        Text {
            text: root.address
            font {
                pixelSize: 17
                bold: true
            }
        }
        Text {
            text: root.stationId
            font.pixelSize: 15
        }
        Text {
            text: root.aqiStatus
            font.pixelSize: 15
        }
    }
}