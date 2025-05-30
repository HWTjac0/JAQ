import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
Rectangle {
    Layout.margins: 0
    Layout.bottomMargin: 0
    Layout.columnSpan: 2
    Layout.fillWidth: true
    Layout.preferredHeight: 150
    color: "#d1e4ff"
    border.width: 1
    border.color: "#bdbdbd"
    radius: 0
    RowLayout {
        anchors.fill: parent
        anchors.margins: 7
        spacing: 2
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#eef7ff"
            border.color: "#cdcdcd"
            border.width: 1
            radius: 15
            CitySelection {}
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#eef7ff"
            border.color: "#cdcdcd"
            border.width: 1
            radius: 15
            AppUtils {}
        }
    }
}