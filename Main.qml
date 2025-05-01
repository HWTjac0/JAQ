import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "./Components"

Window {
    id: window
    visible: true
    width: 600
    height: 480
    title: qsTr("JAirQuality")
    property var context: appContext

    // Convenience aliases
    property var cityHandler: context.cityHandler
    property var stationHandler: context.stationHandler
    property var sensorHandler: context.sensorHandler
    property var sensorDataHandler: context.sensorDataHandler

    Rectangle {
        id: wrapper
        width: parent.width
        height: parent.height
        anchors.fill: parent
        color: "#a1c4fd"
        GridLayout {
            id: mainLayout
            anchors.fill: parent
            columns: 2
            rows: 2
            columnSpacing: 10
            rowSpacing: 0
            TopBar {}
            AsideBar {}
            MainSection {}
        }
    }
}
