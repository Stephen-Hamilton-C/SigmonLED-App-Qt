import QtQuick 2.4
import QtQuick.Controls 2.15

CustomPaletteCreatorForm {

    colorView.delegate: ItemDelegate {
        required property color boxColor
        required property string labelText
        id: itemDelegate
        height: 40
        anchors {
            left: parent.left
            right: parent.right
        }

        Label {
            y: 12
            visible: true
            text: labelText
            anchors.left: parent.left
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 14
            anchors.leftMargin: 50
        }

        Rectangle {
            width: 40
            height: 40
            color: boxColor
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.leftMargin: 0
        }
    }

}
