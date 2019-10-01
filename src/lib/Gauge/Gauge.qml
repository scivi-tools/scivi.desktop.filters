import QtQuick 2.0
import QtQuick.Extras 1.4 as Extras
import QtQuick.Controls.Styles 1.4

Extras.Gauge {
    id: root
    property var color: 'black'
    anchors.margins: 15

    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter

    Behavior on value {
        NumberAnimation {
            duration: 1000
        }
    }

    style: GaugeStyle {
        valueBar: Rectangle {
            id: valueBarRect
            color: root.color
            implicitWidth: 16
        }
    }
}
