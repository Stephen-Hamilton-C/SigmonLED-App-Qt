import QtQuick 2.4
import QtQuick.Controls 2.15

Page {
    id: page
    width: 450
    height: 800
    property alias uploadButton: uploadButton
    property alias colorView: colorView
    title: qsTr("Palette Editor")

    ListView {
        id: colorView
        anchors.fill: parent
        spacing: 3
        anchors.bottomMargin: 100
        model: ListModel {
            ListElement {
                name: "Color 1"
                colorCode: "grey"
            }

            ListElement {
                name: "Color 2"
                colorCode: "red"
            }

            ListElement {
                name: "Color 3"
                colorCode: "blue"
            }

            ListElement {
                name: "Color 4"
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

/*##^##
Designer {
    D{i:0;formeditorZoom:1.1}
}
##^##*/

