import QtQuick 2.0
import QtCharts 2.2

ChartView {
    property alias series: lineSeries1
    property alias axisX: datetimeXAxis
    property alias axisY: axisY
    property alias color: areaSeries.color
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

    AreaSeries {
        id: areaSeries
        axisX: datetimeXAxis
        axisY: axisY
        upperSeries: LineSeries {
            id: lineSeries1
            name: "LineSeries"
            objectName: "linearLineSeries"
        }
    }
}

