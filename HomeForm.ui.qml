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

    Label {
        id: label
        x: 209
        y: 392
        text: qsTr("Devices")
        anchors.verticalCenter: parent.verticalCenter
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/

