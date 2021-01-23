import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: 450
    height: 800
    enabled: true
    hoverEnabled: true
    wheelEnabled: false

    title: qsTr("Home")

    Text {
        id: statusText
        x: 0
        y: 274
        width: 450
        height: 26
        color: "#ff0000"
        text: qsTr("Unconnected")
        font.pixelSize: 28
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        styleColor: "#000000"
        fontSizeMode: Text.FixedSize
    }

    BusyIndicator {
        id: busyIndicator
        x: 195
        y: 370
        running: false
        wheelEnabled: false
    }

    RoundButton {
        id: onButton
        x: 370
        y: 720
        text: "+"
        enabled: false
    }

    RoundButton {
        id: offButton
        x: 370
        y: 666
        text: "+"
        enabled: false
    }

    Button {
        id: connectButton
        x: 186
        y: 376
        text: qsTr("Connect")
    }
    states: [
        State {
            name: "connected"

            PropertyChanges {
                target: statusText
                x: 0
                y: 64
                color: "#00c800"
                text: qsTr("Connected")
            }

            PropertyChanges {
                target: busyIndicator
                running: false
            }

            PropertyChanges {
                target: onButton
                x: 370
                y: 720
                text: "On"
                enabled: true
            }

            PropertyChanges {
                target: offButton
                text: "Off"
                enabled: true
            }

            PropertyChanges {
                target: connectButton
                x: 175
                y: 350
                text: qsTr("Disconnect")
            }
        },
        State {
            name: "connecting"

            PropertyChanges {
                target: statusText
                color: "#006eff"
                text: qsTr("Connecting...")
            }

            PropertyChanges {
                target: connectButton
                enabled: false
            }

            PropertyChanges {
                target: busyIndicator
                running: true
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/

