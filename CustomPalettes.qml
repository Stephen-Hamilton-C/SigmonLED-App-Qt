import QtQuick 2.4
import QtQuick.Controls 2.15

CustomPalettesForm {
    id: page

    listView {
        delegate: Item {
            //x: 5
            //width: 80
            height: 50
            anchors.left: parent.left
            anchors.right: parent.right
            Row {
                id: row1
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                spacing: 10
                Rectangle {
                    id: colorRect
                    width: 40
                    height: 40
                    color: colorCode
                }

                Label {
                    text: name
                    anchors.verticalCenter: colorRect.verticalCenter
                    anchors.left: colorRect.right
                    anchors.leftMargin: 15
                    font.bold: true
                }

                Button {
                    id: uploadButton
                    text: "U"
                    anchors.right: editButton.left
                    anchors.rightMargin: 10
                    width: 30
                    height: 35
                    onClicked: console.log("Upload")
                }

                Button {
                    id: editButton
                    text: "E"
                    anchors.right: delButton.left
                    anchors.rightMargin: 10
                    width: 30
                    height: 35
                    onClicked: console.log("Edit")
                }

                Button {
                    id: delButton
                    text: "D"
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    width: 30
                    height: 35
                    onClicked: console.log("Del")
                }
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
}
