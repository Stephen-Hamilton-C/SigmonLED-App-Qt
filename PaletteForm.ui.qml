import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: 450
    height: 800
    anchors.fill: parent
    property alias stretchBox: stretchBox
    property alias solidPaletteSwitch: solidPaletteSwitch
    property alias brightnessSlider: brightnessSlider
    property alias delayBox: delayBox
    property alias linearBlendSwitch: linearBlendSwitch
    property alias paletteBox: paletteBox
    property alias applyButton: applyButton

    title: qsTr("Palette")

    ScrollView {
        id: scrollView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: applyButton.top
        anchors.bottomMargin: 12
        contentHeight: 500
        clip: true

        ComboBox {
            id: paletteBox
            y: 155
            anchors.verticalCenter: brightnessSlider.verticalCenter
            anchors.left: brightnessSlider.left
            anchors.right: brightnessSlider.right
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            currentIndex: 0
            anchors.verticalCenterOffset: 80

            model: ["Rainbow", "Rainbow Stripe", "Cloud", "Party", "Ocean", "Lava", "Forest", "Custom"]
        }

        SwitchDelegate {
            id: linearBlendSwitch
            y: 255
            text: qsTr("Linear Blending")
            checked: true
            anchors.verticalCenter: solidPaletteSwitch.verticalCenter
            anchors.left: brightnessSlider.left
            anchors.right: brightnessSlider.right
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            anchors.verticalCenterOffset: 50
        }

        Label {
            id: delayLabel
            x: 179
            y: 317
            text: qsTr("Delay (ms)")
            anchors.verticalCenter: linearBlendSwitch.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 14
            anchors.verticalCenterOffset: 50
            anchors.horizontalCenter: linearBlendSwitch.horizontalCenter
        }

        SpinBox {
            id: delayBox
            y: 345
            anchors.verticalCenter: delayLabel.verticalCenter
            anchors.left: brightnessSlider.left
            anchors.right: brightnessSlider.right
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            editable: true
            stepSize: 5
            to: 4095
            value: 10
            anchors.verticalCenterOffset: 40
        }

        Slider {
            id: brightnessSlider
            x: 100
            y: 75
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            stepSize: 1
            to: 255
            anchors.topMargin: 75
            anchors.rightMargin: 100
            anchors.leftMargin: 100
            value: 255
        }

        Label {
            id: brightnessLabel
            x: 350
            y: 52
            text: "Brightness: " + brightnessSlider.value
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: brightnessSlider.top
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            font.pointSize: 14
            anchors.bottomMargin: 0
        }

        SwitchDelegate {
            id: solidPaletteSwitch
            y: 205
            text: qsTr("Solid Palette")
            anchors.verticalCenter: paletteBox.verticalCenter
            anchors.left: brightnessSlider.left
            anchors.right: brightnessSlider.right
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            anchors.verticalCenterOffset: 50
        }

        Label {
            id: stretchLabel
            x: 183
            y: 412
            text: qsTr("Stretching")
            anchors.verticalCenter: delayBox.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenterOffset: 55
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: delayBox.horizontalCenter
            font.pointSize: 14
        }

        SpinBox {
            id: stretchBox
            y: 440
            anchors.verticalCenter: stretchLabel.verticalCenter
            anchors.left: brightnessSlider.left
            anchors.right: brightnessSlider.right
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            value: 3
            stepSize: 1
            anchors.verticalCenterOffset: 40
            editable: true
            to: 16
            from: 1
        }
    }

    Button {
        id: applyButton
        x: 175
        y: 592
        width: 100
        text: qsTr("Apply")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}D{i:2}D{i:3}D{i:5}D{i:8}D{i:10}D{i:1}
}
##^##*/

