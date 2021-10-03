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
        x: 175
        y: 652
        width: 100
        text: qsTr("Apply")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter
    }

    SpinBox {
        id: stretchBox
        x: 129
        y: 536
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

    Label {
        id: stretchLabel
        x: 183
        y: 508
        text: qsTr("Stretching")
        anchors.verticalCenter: delayBox.verticalCenter
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenterOffset: 55
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: delayBox.horizontalCenter
        font.pointSize: 14
    }

    SwitchDelegate {
        id: solidPaletteSwitch
        x: 138
        y: 301
        width: text.width
        text: qsTr("Solid Palette")
        anchors.verticalCenter: paletteBox.verticalCenter
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: paletteBox.horizontalCenter
        anchors.verticalCenterOffset: 50
    }

    Label {
        id: brightnessLabel
        x: 350
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

    Slider {
        id: brightnessSlider
        x: 100
        y: 150
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

    SpinBox {
        id: delayBox
        x: 129
        y: 441
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
        x: 179
        y: 413
        text: qsTr("Delay (ms)")
        anchors.verticalCenter: linearBlendSwitch.verticalCenter
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 14
        anchors.verticalCenterOffset: 50
        anchors.horizontalCenter: linearBlendSwitch.horizontalCenter
    }

    SwitchDelegate {
        id: linearBlendSwitch
        x: 128
        y: 351
        text: qsTr("Linear Blending")
        checked: true
        anchors.verticalCenter: solidPaletteSwitch.verticalCenter
        anchors.horizontalCenter: solidPaletteSwitch.horizontalCenter
        anchors.verticalCenterOffset: 50
        width: text.width
    }

    ComboBox {
        id: paletteBox
        x: 125
        y: 251
        width: 200
        anchors.verticalCenter: brightnessSlider.verticalCenter
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        currentIndex: 0
        anchors.verticalCenterOffset: 80

        model: ["Rainbow", "Rainbow Stripe", "Cloud", "Party", "Ocean", "Lava", "Forest", "Custom"]
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/
