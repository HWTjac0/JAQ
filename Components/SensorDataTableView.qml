import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    Layout.preferredWidth: 240
    Layout.fillHeight: true
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        HorizontalHeaderView {
            id: sensorDataHeader
            syncView: sensorDataTable
            clip: true
            Layout.preferredHeight: 30
            flickableDirection: Flickable.VerticalFlick
            delegate: Item {
                implicitHeight: 30
                Rectangle {
                    anchors.fill: parent
                    color: "#5287ec"
                    topLeftRadius: {
                        if (model.column === 0) return 8
                        return 0
                    }
                    topRightRadius: {
                        if (model.column === 1) return 8
                        return 0
                    }
                    Text {
                        anchors.centerIn: parent
                        text: display
                        font {
                            bold: true
                            pixelSize: 15
                        }
                        color: "white"
                    }
                }
            }
        }
        SensorDataTable {
            id: sensorDataTable
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: sensorDataHandler.sensordataModel
        }
    }
}