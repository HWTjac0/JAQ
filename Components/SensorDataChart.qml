import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtCharts
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ChartView {
    id: sensordataChart
    title: "Dane pomiarowe wskaźnika"
    Layout.fillWidth: true
    Layout.fillHeight: true
    antialiasing: true
    animationOptions: ChartView.NoAnimation
    visible: false
    LineSeries {
        id: sensordataSeries
        axisX: DateTimeAxis {
            id: datetimeAxis
            min: sensorDataModel.timerangeStart
            max: sensorDataModel.timerangeEnd
        }
        axisY: ValueAxis {
            id: valueAxis
            min: sensorDataModel.minValue
            max: sensorDataModel.maxValue
        }
    }
    Connections {
        target: sensorDataHandler
        function onDataChanged() {
            sensordataChart.visible = true
            datetimeAxis.min    = sensorDataModel.timerangeStart
            datetimeAxis.max    = sensorDataModel.timerangeEnd
            valueAxis.min       = sensorDataModel.minValue
            valueAxis.max       = sensorDataModel.maxValue
            sensorDataModel.fillSeries(sensordataSeries)
        }
    }
}