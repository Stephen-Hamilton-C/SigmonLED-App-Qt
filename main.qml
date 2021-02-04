import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    id: window
    width: 450
    height: 800
    visible: true
    title: qsTr("Stack")

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: "\u2630" //stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                drawer.open()
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Devices")
                width: parent.width
                onClicked: {
                    if(stackView.children[stackView.children.length-1].toString().split('.')[0].search("HomeForm") === -1){
                        stackView.clear()
                        stackView.push("HomeForm.ui.qml")
                    }
                    drawer.close()
                }
            }

            ItemDelegate {
                text: qsTr("Static Color")
                width: parent.width
                onClicked: {
                    if(stackView.children[stackView.children.length-1].toString().split('.')[0].search("StaticColor") === -1){
                        stackView.clear()
                        stackView.push("StaticColor.ui.qml")
                    }
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Palette")
                width: parent.width
                onClicked: {
                    if(stackView.children[stackView.children.length-1].toString().split('.')[0].search("Palette") === -1){
                        stackView.clear()
                        stackView.push("Palette.ui.qml")
                    }
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "HomeForm.ui.qml"
        anchors.fill: parent
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
