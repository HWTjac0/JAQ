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
                id: cityCombo
                Layout.alignment: Qt.AlignHCenter
                implicitContentWidthPolicy: ComboBox.WidestTextWhenCompleted
                model: cityHandler.getCities()
                textRole: "display"

                height: 40  // Set your desired fixed height
                    implicitHeight: height
                delegate: ItemDelegate {
                    width: cityCombo.width
                    text: model.display
                    highlighted: cityCombo.highlightedIndex === index
                }
                onActivated: {
                    console.log(cityCombo.model.id)
                }
            }
            Button {
                Layout.alignment: Qt.AlignHCenter
                text: "Sprawdź"
            }
            Test {}
        }
    }
}
