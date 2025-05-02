import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    anchors.fill: parent
    anchors.margins: 5
    spacing: 5
    Text {
        Layout.leftMargin: 15
        text: "Wybór miasta"
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
            height: parent.height
            anchors.margins: 20
            columns: 2
            rows: 2
            columnSpacing: 5
            rowSpacing: 5
            Label {
                id: voivodeshipLabel
                text: "Województwo"
            }
            ComboBox {
                model: cityHandler.voivodeshipModel
                onActivated: cityHandler.getCities().filterVoivodeship = currentText
                Component.onCompleted: {
                    cityHandler.getCities().filterVoivodeship = currentText
                }
            }
            Label {
                id: cityLabel
                text: "Miasto"
            }
            ComboBox {
                id: cityCombo
                model: cityHandler.getCities()
                textRole: "cityName"
                onActivated: {
                    cityHandler.citySelected(currentIndex)
                }
                Connections {
                    target: cityHandler.getCities()
                    function onFilterVoivodeshipChanged() {
                        cityCombo.currentIndex = 0
                    }
                }

            }
        }
    }
}