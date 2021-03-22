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
        id: button
        text: qsTr("Add New...")
        anchors.left: listView.left
        anchors.right: listView.right
        anchors.top: listView.bottom
        font.letterSpacing: 1
        font.pointSize: 12
        font.wordSpacing: 1
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
    }
}
