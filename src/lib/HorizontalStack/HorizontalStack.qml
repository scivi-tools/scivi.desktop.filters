import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4 as OldControls

OldControls.SplitView {
    property alias visual1Container: visual1Container
    property alias visual2Container: visual2Container
    orientation: Qt.Horizontal

    anchors.fill: parent

    Pane {
        id: visual1Container
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: parent.width / 2
    }
    Pane {
        id: visual2Container
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.right: parent.right
        width: parent.width / 2
    }
}
