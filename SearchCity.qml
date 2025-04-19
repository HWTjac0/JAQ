import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    width: 300
    height: 60
    ColumnLayout {
        anchors.fill: parent
        spacing: 5
        TextField {
            id: searchField
            implicitWidth: 200
            padding: 7
            Layout.alignment: Qt.AlignHCenter
            placeholderText: "Wyszukaj miasto..."
            onTextChanged: cityHandler.getCities().filterString = text
        }

        ComboBox {
            id: cityCombo
            Layout.alignment: Qt.AlignHCenter
            model: cityHandler.getCities()
            textRole: "display"
            implicitContentWidthPolicy: ComboBox.WidestTextWhenCompleted
            popup: Popup {
                width: cityCombo.width
                y: cityCombo.height - 1
                padding: 1
                implicitHeight: 200
                height:  Math.min(300, ListView.contentHeight)
                closePolicy: Popup.CloseOnEscape
                focus: true
                contentItem: ListView {
                    clip: true
                    implicitHeight: contentHeight
                    model: cityCombo.popup.visible ? cityCombo.delegateModel : null
                    currentIndex: cityCombo.highlightedIndex
                    interactive: true
                    ScrollIndicator.vertical: ScrollIndicator {
                        visible: ListView.contentHeight > height
                    }
                }
            }

            delegate: ItemDelegate {
               width: cityCombo.popup.width
               text: model.display
               highlighted: cityCombo.highlightedIndex === index
           }
            onActivated: {
                console.log("Selected City ID:", cityHandler.getCityId(currentIndex))
            }
        }
    }
}
