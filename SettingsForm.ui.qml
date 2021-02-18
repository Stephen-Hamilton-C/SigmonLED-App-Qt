import QtQuick 2.4
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 450
    height: 800
    property alias autoConnectSwitch: autoConnectSwitch
    property alias darkModeSwitch: darkModeSwitch

    Page {
        id: page
        anchors.fill: parent

        Column {
            id: column
            anchors.fill: parent

            SwitchDelegate {
                id: darkModeSwitch
                text: qsTr("Dark Mode")
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 0
                anchors.rightMargin: 0
            }

            SwitchDelegate {
                id: autoConnectSwitch
                text: qsTr("Auto-Connect")
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 0
                anchors.rightMargin: 0
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}D{i:2}D{i:1}
}
##^##*/

