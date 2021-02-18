import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: 450
    height: 800
    anchors.fill: parent
    property alias solidPaletteSwitch: solidPaletteSwitch
    property alias brightnessSlider: brightnessSlider
    property alias delayBox: delayBox
    property alias linearBlendSwitch: linearBlendSwitch
    property alias paletteBox: paletteBox
    property alias applyButton: applyButton

    title: qsTr("Palette")

    Button {
        id: applyButton
        x: 188
        y: 689
        width: 100
        text: qsTr("Apply")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ComboBox {
        id: paletteBox
        x: 165
        y: 226
        width: 200
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        currentIndex: 0
        anchors.verticalCenterOffset: -75

        model: ["Rainbow", "Rainbow Stripe", "Cloud", "Party", "Ocean", "Lava", "Forest"]
    }

    SwitchDelegate {
        id: linearBlendSwitch
        x: 125
        y: 453
        text: qsTr("Linear Blending")
        checked: true
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: 25
        width: text.width
    }

    SpinBox {
        id: delayBox
        x: 129
        y: 487
        anchors.verticalCenter: parent.verticalCenter
        editable: true
        stepSize: 10
        to: 9999
        value: 10
        anchors.verticalCenterOffset: 125
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: delayLabel
        x: 206
        y: 455
        text: qsTr("Delay (ms)")
        anchors.verticalCenter: parent.verticalCenter
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 14
        anchors.verticalCenterOffset: 85
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Slider {
        id: brightnessSlider
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        stepSize: 1
        to: 255
        anchors.topMargin: 150
        anchors.rightMargin: 100
        anchors.leftMargin: 100
        value: 255
    }

    Label {
        id: brightnessLabel
        y: 127
        text: "Brightness: " + brightnessSlider.value
        anchors.left: brightnessSlider.right
        anchors.right: brightnessSlider.left
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
        x: 0
        y: 449
        width: text.width
        text: qsTr("Solid Palette")
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: -25
    }
}
