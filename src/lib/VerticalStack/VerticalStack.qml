import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4 as OldControls

OldControls.SplitView {
    property alias visual1Container: visual1Container
    property alias visual2Container: visual2Container
    orientation: Qt.Vertical

    anchors.fill: parent

    Pane {
        id: visual1Container
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height / 2
    }
    Pane {
        id: visual2Container
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height / 2
    }
}
