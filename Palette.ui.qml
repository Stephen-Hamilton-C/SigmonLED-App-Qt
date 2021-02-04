import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: 450
    height: 800

    title: qsTr("Palette")

    Label {
        text: qsTr("Palette Page")
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 12
        anchors.leftMargin: 0
        anchors.rightMargin: 0
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
