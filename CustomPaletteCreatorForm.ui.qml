import QtQuick 2.4
import QtQuick.Controls 2.15

Page {
    id: page
    width: 450
    height: 800
    title: qsTr("Palette Editor")

    ListView {
        id: colorView
        anchors.fill: parent
        spacing: 3
        anchors.bottomMargin: 100
        delegate: ItemDelegate {
            anchors {
                left: parent.left
                right: parent.right
            }

            text: name
            Label {
                text: name
            }

            Rectangle {
                width: 40
                height: 40
                color: colorCode
            }
        }
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
    }

    Button {
        id: uploadButton
        x: 188
        y: 723
        text: qsTr("Button")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
    }
}
