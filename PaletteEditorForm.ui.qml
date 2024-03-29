import QtQuick 2.4
import QtQuick.Controls 2.15

Page {
    id: page
    width: 450
    height: 800
    enabled: true
    hoverEnabled: true
    wheelEnabled: false
    anchors.fill: parent
    property alias saveButton: saveButton
    property alias nameField: nameField
    property alias gridView: gridView

    TextField {
        id: nameField
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        anchors.topMargin: 50
        anchors.leftMargin: 25
        anchors.rightMargin: 25
        placeholderText: qsTr("Custom Palette Name")
    }

    GridView {
        id: gridView
        anchors.left: nameField.left
        anchors.right: nameField.right
        anchors.top: nameField.bottom
        anchors.bottom: parent.bottom
        cellHeight: 75
        cellWidth: 75
        highlightRangeMode: GridView.NoHighlightRange
        anchors.bottomMargin: 200
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
    }

    Button {
        id: saveButton
        x: 191
        text: qsTr("Save")
        anchors.top: gridView.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 102
        anchors.bottomMargin: 50
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/

