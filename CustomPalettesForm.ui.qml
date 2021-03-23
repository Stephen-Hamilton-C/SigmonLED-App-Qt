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
    property alias sendingProgress: sendingProgress
    property alias sendingLabel: sendingLabel
    property alias sendingDialog: sendingDialog
    property alias createButton: createButton
    property alias listView: listView

    title: qsTr("Custom Palettes")

    ListView {
        id: listView
        anchors.fill: parent
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.topMargin: 10
        anchors.bottomMargin: 100
    }

    Button {
        id: createButton
        text: qsTr("Add New...")
        anchors.left: listView.left
        anchors.right: listView.right
        anchors.top: listView.bottom
        font.letterSpacing: 1
        enabled: true
        font.pointSize: 12
        font.wordSpacing: 1
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
    }

    Rectangle {
        id: sendingDialog
        color: "#80ffffff"
        anchors.fill: parent
        z: 2
        visible: true

        ProgressBar {
            id: sendingProgress
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            to: 0
            from: 1
            indeterminate: false
            anchors.rightMargin: 25
            anchors.leftMargin: 25
            value: 0
        }

        ProgressBar {
            id: sendingProgressEffect
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: sendingProgress.bottom
            anchors.topMargin: 0
            indeterminate: true
            anchors.rightMargin: 25
            anchors.leftMargin: 25
        }

        ProgressBar {
            id: sendingProgressEffect2
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: sendingProgress.top
            anchors.bottomMargin: 0
            indeterminate: true
            anchors.rightMargin: 25
            anchors.leftMargin: 25
        }

        Label {
            id: sendingLabel
            x: 209
            y: 249
            text: qsTr("Uploading Palette...")
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -30
            anchors.horizontalCenter: parent.horizontalCenter
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
    }
}
