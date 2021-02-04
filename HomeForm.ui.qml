import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: 450
    height: 800
    enabled: true
    hoverEnabled: true
    wheelEnabled: false

    title: qsTr("Devices")

    BusyIndicator {
        id: busyIndicator
        x: 195
        y: 370
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        running: false
    }

    Label {
        id: connLabel
        x: 209
        color: "#ff0000"
        text: qsTr("Not connected")
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.topMargin: 50
        font.pointSize: 16
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Button {
        id: connButton
        x: 191
        width: 100
        text: qsTr("Connect")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.8999999761581421}D{i:2}
}
##^##*/

