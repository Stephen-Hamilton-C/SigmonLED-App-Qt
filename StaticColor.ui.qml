import QtQuick 2.12
import QtQuick.Controls 2.12

Page {
    id: page
    width: 450
    height: 800
    font.pointSize: 11

    title: qsTr("Static Color")

    Button {
        id: applyButton
        x: 188
        y: 689
        width: 100
        text: qsTr("Apply")
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 100
    }

    // Source: https://stackoverflow.com/questions/42707818/customizing-slider-in-qt-5-6-qml
    Slider {
        id: hueSlider
        y: 159
        width: 30
        height: 300
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        to: 255
        snapMode: Slider.SnapAlways
        value: 0
        anchors.leftMargin: 75
        stepSize: 1
        orientation: Qt.Vertical

        background: Rectangle {
            x: hueSlider.leftPadding + (hueHorizontal ? 0 : (hueSlider.availableWidth - width) / 2)
            y: hueSlider.topPadding + (hueHorizontal ? (hueSlider.availableHeight - height) / 2 : 0)
            implicitWidth: hueHorizontal ? 200 : 10
            implicitHeight: hueHorizontal ? 10 : 200
            width: hueHorizontal ? hueSlider.availableWidth : implicitWidth
            height: hueHorizontal ? implicitHeight : hueSlider.availableHeight
            radius: 10
            border.color: "#000000"
            color: Qt.hsva(hueSlider.value/255.0, 1, 1, 1)
            scale: hueHorizontal && hueSlider.mirrored ? -1 : 1

            readonly property bool hueHorizontal: hueSlider.orientation === Qt.Horizontal
        }
    }

    Slider {
        id: satSlider
        y: 159
        width: 30
        height: 300
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: -75
        to: 255
        snapMode: Slider.SnapAlways
        value: 0
        stepSize: 1
        orientation: Qt.Vertical

        background: Rectangle {
            x: satSlider.leftPadding + (satHorizontal ? 0 : (satSlider.availableWidth - width) / 2)
            y: satSlider.topPadding + (satHorizontal ? (satSlider.availableHeight - height) / 2 : 0)
            implicitWidth: satHorizontal ? 200 : 10
            implicitHeight: satHorizontal ? 10 : 200
            width: satHorizontal ? satSlider.availableWidth : implicitWidth
            height: satHorizontal ? implicitHeight : satSlider.availableHeight
            radius: 10
            border.color: "#000000"
            color: Qt.hsva(hueSlider.value/255.0, satSlider.value/255.0, 1, 1)
            scale: satHorizontal && satSlider.mirrored ? -1 : 1

            readonly property bool satHorizontal: satSlider.orientation === Qt.Horizontal
        }
    }

    Slider {
        id: valSlider
        y: 159
        width: 30
        height: 300
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 75
        anchors.verticalCenterOffset: 0
        to: 255
        snapMode: Slider.SnapAlways
        value: 0
        stepSize: 1
        orientation: Qt.Vertical

        background: Rectangle {
            x: valSlider.leftPadding + (valHorizontal ? 0 : (valSlider.availableWidth - width) / 2)
            y: valSlider.topPadding + (valHorizontal ? (valSlider.availableHeight - height) / 2 : 0)
            implicitWidth: valHorizontal ? 200 : 10
            implicitHeight: valHorizontal ? 10 : 200
            width: valHorizontal ? valSlider.availableWidth : implicitWidth
            height: valHorizontal ? implicitHeight : valSlider.availableHeight
            radius: 10
            border.color: "#000000"
            //color: "#ffffff"
            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: satSlider.background.color
                }
                GradientStop {
                    position: 1.0
                    color: "black"
                }
            }
            scale: valHorizontal && valSlider.mirrored ? -1 : 1

            readonly property bool valHorizontal: valSlider.orientation === Qt.Horizontal
        }
    }

    Rectangle {
        id: colorPreview
        x: 125
        y: 506
        width: 50
        height: 50
        color: Qt.hsva(hueSlider.value/255, satSlider.value/255, valSlider.value/255, 1)
        radius: 10
        border.width: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 200
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: hueLabel
        x: 0
        y: 0
        text: qsTr("Hue: " + hueSlider.value)
        anchors.bottom: hueSlider.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenter: hueSlider.horizontalCenter
        font.pointSize: 16
        anchors.bottomMargin: 0
    }

    Label {
        id: satLabel
        x: 0
        y: 0
        text: qsTr("Saturation: " + satSlider.value)
        anchors.bottom: satSlider.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenter: satSlider.horizontalCenter
        font.pointSize: 16
        anchors.bottomMargin: 0
    }

    Label {
        id: valLabel
        x: 0
        y: 0
        text: qsTr("Brightness: " + valSlider.value)
        anchors.bottom: valSlider.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenter: valSlider.horizontalCenter
        font.pointSize: 16
        anchors.bottomMargin: 0
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/

