import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

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
                text: "Podaj miasto"
                font.pixelSize: 20
                font.bold: true
            }
            TextField {
                id: cityInput
                onAccepted: cityHandler.receiveText(text)
                Layout.alignment: Qt.AlignHCenter
                placeholderText: qsTr("np. Warszawa")
                font.pixelSize: 12
                topPadding: 8
                bottomPadding: 8
                leftPadding: 13
                rightPadding: 13
                Layout.preferredWidth: 200
            }
            Button {
                Layout.alignment: Qt.AlignHCenter
                text: "Szukaj"
                onPressed: cityHandler.receiveText(cityInput.text)
            }
        }
    }
}
