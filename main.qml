import QtQuick 2.12
import QtQuick.Controls 2.5
import com.stephenhamilton.sigmonled 1.0

ApplicationWindow {
    id: window
    width: 450
    height: 800
    visible: true
    title: qsTr("Stack")

    property string currentPage: "Devices"

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: "\u2630" //stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                drawer.open()
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

    HomeForm {
        id: homeForm
        visible: true
        anchors.fill: parent

        DeviceManager {
            id: deviceMan
        }

        HomeBackend {
            id: homeBack
        }

        connButton.onClicked: homeBack.connectToTestDevice()

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
