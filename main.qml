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
                    /*
                    if(stackView.children[stackView.children.length-1].toString().split('.')[0].search("HomeForm") === -1){
                        stackView.clear()
                        stackView.push("HomeForm.ui.qml")
                    }
                    */

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
                    /*
                    if(stackView.children[stackView.children.length-1].toString().split('.')[0].search("StaticColor") === -1){
                        stackView.clear()
                        stackView.push("StaticColor.ui.qml")
                    }
                    */

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
                    /*
                    if(stackView.children[stackView.children.length-1].toString().split('.')[0].search("Palette") === -1){
                        stackView.clear()
                        stackView.push("Palette.ui.qml")
                    }
                    */

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
    HomeForm {
        id: homeForm
        visible: true
        anchors.fill: parent

        DeviceManager {
            id: deviceMan


            onBLEStartedSearch: {
                homeForm.searchIndicator.running = true
            }

            onBLEStoppedSearch: {
                homeForm.searchIndicator.running = false
            }

            onBLEConnect: {
                homeForm.connLabel.text = "Connected"
                homeForm.connLabel.color = "#0099ff"
                homeForm.connButton.text = "Disconnect"
            }

            onBLEReady: {
                homeForm.connLabel.text = "Ready"
                homeForm.connLabel.color = "#00aa00"
                homeForm.connButton.text = "Disconnect"
            }

            onBLEConnecting: {
                homeForm.connLabel.text = "Connecting..."
                homeForm.connLabel.color = "#aaaa00"
            }

            onBLEDisconnect: {
                homeForm.connLabel.text = "Disconnected"
                homeForm.connLabel.color = "#ff0000"
                homeForm.connButton.text = "Connect"
            }

            onBLEFault: {
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
                text: modelData.substring(0, modelData.length-18)
                highlighted: homeBack.highlightedDelegate == modelData


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

    /*
    StackView {
        id: stackView
        initialItem: homeForm
        anchors.fill: parent
    }
    */
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
