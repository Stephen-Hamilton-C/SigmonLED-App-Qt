import QtQuick 2.12
import QtQuick.Controls 2.5
import com.stephenhamilton.sigmonled.main 1.0

ApplicationWindow {
    id: window
    width: 450
    height: 800
    visible: true
    title: qsTr("SigmonLED")

    property string currentPage: "Devices"

    header: ToolBar {
        contentHeight: menuButton.implicitHeight

        ToolButton {
            id: menuButton
            text: "\u2630" //stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                drawer.open()
            }
        }

        ToolButton {
            id: searchButton
            text: "\u27F3" //U+21BB
            font.pixelSize: Qt.application.font.pixelSize * 2
            anchors.right: parent.right
            visible: homeForm.visible
            onClicked: {
                deviceMan.startDiscovery()
            }
        }

        Label {
            text: currentPage
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Devices")
                width: parent.width
                onClicked: {
                    homeForm.visible = true
                    colorForm.visible = false
                    paletteForm.visible = false
                    currentPage = text
                    drawer.close()
                }
            }

            ItemDelegate {
                text: qsTr("Static Color")
                width: parent.width
                enabled: deviceMan.ready
                onClicked: {
                    homeForm.visible = false
                    colorForm.visible = true
                    paletteForm.visible = false
                    currentPage = text
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Palette")
                width: parent.width
                enabled: deviceMan.ready
                onClicked: {
                    homeForm.visible = false
                    colorForm.visible = false
                    paletteForm.visible = true
                    currentPage = text
                    drawer.close()
                }
            }
        }
    }

    //Probably should make some Qml files and put the linkage there instead of here
    //Or perhaps use Qt Designer's backend system
    HomeForm {
        id: homeForm
        visible: true
        anchors.fill: parent

        DeviceManager {
            id: deviceMan


            onOnBLEStartedSearch: {
                homeForm.searchIndicator.running = true
            }

            onOnBLEStoppedSearch: {
                homeForm.searchIndicator.running = false
            }

            onOnBLEConnect: {
                homeForm.connLabel.text = "Connected"
                homeForm.connLabel.color = "#0099ff"
                homeForm.connButton.text = "Disconnect"
            }

            onOnBLEReady: {
                homeForm.connLabel.text = "Ready"
                homeForm.connLabel.color = "#00aa00"
                homeForm.connButton.text = "Disconnect"
            }

            onOnBLEConnecting: {
                homeForm.connLabel.text = "Connecting..."
                homeForm.connLabel.color = "#aaaa00"
            }

            onOnBLEDisconnect: {
                homeForm.connLabel.text = "Disconnected"
                homeForm.connLabel.color = "#ff0000"
                homeForm.connButton.text = "Connect"
            }

            onOnBLEFault: {
                homeForm.connLabel.text = "Err: "+errMsg
                homeForm.connLabel.text = "Disconnected"
                homeForm.connLabel.color = "#ff0000"
                homeForm.connButton.text = "Connect"
            }
        }

        HomeBackend {
            id: homeBack
        }

        connButton.onClicked: homeBack.connectPressed()
        showAllButton.onActivated: {
            homeBack.showAll = !homeBack.showAll
            showAllButton.text = homeBack.showAll ? "Hide" : "Show All"
        }

        devicesList {
            model: homeBack.devices
            delegate: ItemDelegate {
                required property string modelData
                width: 100
                anchors {
                    left: parent.left
                    right: parent.right
                }
                //Remove the encoded MAC address from the modelData
                text: modelData.substring(0, modelData.length-18)
                //Highlight if selected
                highlighted: homeBack.highlightedDelegate == modelData

                //select on click
                onClicked: homeBack.highlightedDelegate = modelData
            }
        }


    }

    Palette {
        id: paletteForm
        visible: false
        anchors.fill: parent

        PaletteBackend {
            id: paletteBack
        }

        brightnessSlider {
            onValueChanged: paletteBack.setBrightness(brightnessSlider.value)
        }

        delayBox {
            onValueChanged: paletteBack.setDelay(delayBox.value)
        }

        solidPaletteSwitch {
            onCheckedChanged: paletteBack.setSolidPalette(solidPaletteSwitch.checked);
        }

        linearBlendSwitch {
            onCheckedChanged: paletteBack.setLinearBlending(linearBlendSwitch.checked)
        }

        paletteBox {
            onActivated: paletteBack.setPalette(paletteBox.currentText)
        }

        applyButton {
            onClicked: paletteBack.ApplyChanges()
        }

    }

    StaticColor {
        id: colorForm
        visible: false
        anchors.fill: parent

        StaticColorBackend {
            id: colorBack
        }

        applyButton {
            onClicked: colorBack.Apply()
        }

        hueSlider {
            onValueChanged: colorBack.setH(hueSlider.value)
        }

        satSlider {
            onValueChanged: colorBack.setS(satSlider.value)
        }

        valSlider {
            onValueChanged: colorBack.setV(valSlider.value)
        }

    }

    //Fast buttons - simple on/off buttons that sit in the corner to easily turn LEDs on and off
    FastBackend {
        id: fastBack
    }

    RoundButton {
        id: fastOnButton
        text: "On"
        anchors.bottom: fastOffButton.top
        anchors.horizontalCenter: fastOffButton.horizontalCenter
        anchors.bottomMargin: 0
        enabled: deviceMan.ready
        onClicked: fastBack.on()
    }

    RoundButton {
        id: fastOffButton
        text: "Off"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 25
        anchors.bottomMargin: 50
        enabled: deviceMan.ready
        onClicked: fastBack.off()
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
