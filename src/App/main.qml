import QtQuick 2.10
import QtQuick.Window 2.10
import QtCharts 2.2
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        anchors.fill: parent
        objectName: "myRect"
    }
}
