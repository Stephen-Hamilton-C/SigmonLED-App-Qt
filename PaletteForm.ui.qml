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
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        currentIndex: 0
        anchors.verticalCenterOffset: -125

        model: ["Rainbow", "Rainbow Stripe", "Cloud", "Party", "Ocean", "Lava", "Forest", "Custom"]
    }

    SwitchDelegate {
        id: linearBlendSwitch
        x: 125
        y: 453
        text: qsTr("Linear Blending")
        checked: true
        anchors.verticalCenter: solidPaletteSwitch.verticalCenter
        anchors.horizontalCenter: solidPaletteSwitch.horizontalCenter
        anchors.verticalCenterOffset: 50
        width: text.width
    }

    SpinBox {
        id: delayBox
        x: 129
        y: 487
        anchors.verticalCenter: delayLabel.verticalCenter
        anchors.horizontalCenterOffset: 0
        editable: true
        stepSize: 5
        to: 4095
        value: 10
        anchors.verticalCenterOffset: 40
        anchors.horizontalCenter: delayLabel.horizontalCenter
    }

    Label {
        id: delayLabel
        text: qsTr("Delay (ms)")
        anchors.verticalCenter: linearBlendSwitch.verticalCenter
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 14
        anchors.verticalCenterOffset: 50
        anchors.horizontalCenter: linearBlendSwitch.horizontalCenter
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
        anchors.verticalCenter: paletteBox.verticalCenter
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: paletteBox.horizontalCenter
        anchors.verticalCenterOffset: 50
    }

    Label {
        id: stretchLabel
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
        x: 132
        y: 488
        anchors.verticalCenter: stretchLabel.verticalCenter
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: stretchLabel.horizontalCenter
        value: 3
        stepSize: 1
        anchors.verticalCenterOffset: 40
        editable: true
        to: 16
        from: 1
    }
}
