import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: 450
    height: 800

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
        anchors.verticalCenterOffset: -25

        model: ["Rainbow",
                "Rainbow Stripe",
                "Cloud",
                "Party",
                "Ocean",
                "Lava",
                "Forest"
        ]
    }

    SwitchDelegate {
        id: linearBlendSwitch
        x: 125
        y: 453
        text: qsTr("Linear Blending")
        anchors.verticalCenter: parent.verticalCenter
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
        id: label
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
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}D{i:1}D{i:2}D{i:3}
}
##^##*/

