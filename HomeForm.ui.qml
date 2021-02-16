import QtQuick 2.12
import QtQuick.Controls 2.5
import com.stephenhamilton.sigmonled.main 1.0

Page {
    id: page
    width: 450
    height: 800
    enabled: true
    hoverEnabled: true
    wheelEnabled: false
    anchors.fill: parent
    property alias showAllButton: showAllButton
    property alias connLabel: connLabel
    property alias searchIndicator: searchIndicator
    property alias devicesList: devicesList
    property alias connButton: connButton

    title: qsTr("Devices")

    Button {
        id: connButton
        x: 175
        y: 396
        width: 100
        text: qsTr("Connect")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: connLabel
        x: 158
        color: "#ff0000"
        text: qsTr("Disconnected")
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.topMargin: 25
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 16
    }

    BusyIndicator {
        id: searchIndicator
        x: 195
        anchors.top: parent.top
        anchors.topMargin: 75
        anchors.horizontalCenter: parent.horizontalCenter
        running: true
    }

    ListView {
        id: devicesList
        x: 0
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: searchIndicator.running ? 150 : 50
        anchors.bottomMargin: 125
        anchors.leftMargin: 0
        anchors.rightMargin: 0

        DelayButton {
            id: showAllButton
            height: 36
            text: qsTr("Show all")
            anchors.left: parent.left
            anchors.top: parent.bottom
            font.pointSize: 9
            anchors.leftMargin: 15
            anchors.topMargin: 0
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/

