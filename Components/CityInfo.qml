import QtQuick
import QtQuick.Layouts

Item {
    id: root
    property string cityName: "Miasto: <wybierz z listy>"
    property string voivodeship: "Województwo: <po wybraniu miasta>"
    property string county: "Powiat: <po wybraniu miasta>"
    property string commune: "Gmina: <po wybraniu miasta>"

    Layout.fillWidth: true
    Layout.preferredHeight: childrenRect.height
    Column {
        anchors.top: root.top
        spacing: 5

        Text {
            text: root.cityName
            font {
                pixelSize: 30
                bold: true
            }
        }
        Text {
            text: root.voivodeship
            font.pixelSize: 20
        }
        Text {
            text: root.county
            font.pixelSize: 20
        }
        Text {
            text: root.commune
            font.pixelSize: 20
        }
    }
}