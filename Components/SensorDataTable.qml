import QtQuick
import QtQuick.Controls

TableView {
    id: root
    clip: true
    flickableDirection: Flickable.VerticalFlick

    ScrollBar.vertical: ScrollBar {
        policy: ScrollBar.AsNeeded
    }

    columnWidthProvider: function(column) { return 120 }
    rowHeightProvider: function(row) { return 30 }

    delegate: Rectangle {
        implicitWidth: 150
        implicitHeight: 40
        border.width: 1

        Text {
            anchors.fill: parent
            anchors.margins: 5
            text: {
                if (column === 0) {
                    return Qt.formatDateTime(sensordataTimestamp, "yyyy-MM-dd hh:mm")
                } else {
                    return sensordataValue.toFixed(2)
                }
            }
            verticalAlignment: Text.AlignVCenter
        }
    }
}