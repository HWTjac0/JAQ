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
                text: "Wybierz miasto"
                font.pixelSize: 20
                font.bold: true
            }
            ComboBox {
                id: city
                Layout.alignment: Qt.AlignHCenter
                model: cityHandler.getCities()
                onActivated: cityHandler.receiveText(city.currentText)
            }
            Button {
                Layout.alignment: Qt.AlignHCenter
                text: "Sprawdź"
                onPressed: cityHandler.receiveText(city.currentText)
            }
        }
    }
}
