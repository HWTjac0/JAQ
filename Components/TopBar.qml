import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
Rectangle {
    Layout.margins: 0
    Layout.bottomMargin: 0
    Layout.columnSpan: 2
    Layout.fillWidth: true
    Layout.preferredHeight: 140
    color: "#e9f1fd"
    border.width: 1
    border.color: "#bdbdbd"
    radius: 0
    RowLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 15
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#eef7ff"
            border.color: "#cdcdcd"
            border.width: 1
            radius: 20
            bottomLeftRadius: 4
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
                    ComboBox {
                        model: ["zachodniopomorskie", "mazowieckie"]
                    }
                }
            }
        }
    }
}