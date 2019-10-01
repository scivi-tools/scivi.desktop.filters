import QtQuick 2.0
import QtCharts 2.2

ChartView {
    property alias series: lineSeries1
    property alias axisX: lineSeries1.axisX
    property alias axisY: lineSeries1.axisY
    property alias color: lineSeries1.color
    property var xType: "real"

    anchors.fill: parent
    legend.visible: false
    antialiasing: true
    objectName: "chartView"

    ValueAxis {
        id: axisY
        min: 0
        max: 1
    }

    DateTimeAxis {
        id: datetimeXAxis
    }

    LineSeries {
        id: lineSeries1
        name: "LineSeries"
        objectName: "linearLineSeries"
        axisY: axisY
        axisX: datetimeXAxis
    }
}

