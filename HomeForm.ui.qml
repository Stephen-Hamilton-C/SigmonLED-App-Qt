import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: 450
    height: 800
    enabled: true
    hoverEnabled: true
    wheelEnabled: false

    title: qsTr("Home")

    Text {
        id: text1
        x: 178
        width: page.width
        height: 21
        color: "#ff0000"
        text: qsTr("Searching...")
        anchors.top: parent.top
        font.pixelSize: 24
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        minimumPointSize: 12
        minimumPixelSize: 12
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}D{i:1}
}
##^##*/

