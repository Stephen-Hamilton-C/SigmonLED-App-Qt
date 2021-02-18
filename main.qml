import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12
import StephenHamilton.SigmonLED.Main 1.0

ApplicationWindow {
    id: window
    width: 450
    height: 800
    visible: true
    title: qsTr("SigmonLED")

    property string currentPage: "Devices"

    Material.theme: settingsPage.darkMode ? "Dark" : "Light"

    header: ToolBar {
        contentHeight: menuButton.implicitHeight

        ToolButton {
            id: menuButton
            icon.source: "icons/menu"
            icon.color: white
            onClicked: {
                drawer.open()
            }
        }

        ToolButton {
            id: searchButton
            icon.source: "icons/refresh"
            icon.color: white
            anchors.right: parent.right
            visible: homePage.visible
            onClicked: {
                deviceMan.startDiscovery()
            }
        }

        Label {
            text: currentPage
            color: "#FFFFFF"
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
                    homePage.visible = true
                    colorPage.visible = false
                    palettePage.visible = false
                    settingsPage.visible = false
                    currentPage = text
                    drawer.close()
                    console.log("Dark mode: "+settingsPage.darkMode)
                }
            }

            ItemDelegate {
                text: qsTr("Static Color")
                width: parent.width
                enabled: deviceMan.ready
                onClicked: {
                    homePage.visible = false
                    colorPage.visible = true
                    palettePage.visible = false
                    settingsPage.visible = false
                    currentPage = text
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Palette")
                width: parent.width
                enabled: deviceMan.ready
                onClicked: {
                    homePage.visible = false
                    colorPage.visible = false
                    palettePage.visible = true
                    settingsPage.visible = false
                    currentPage = text
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Settings")
                width: parent.width
                onClicked: {
                    homePage.visible = false
                    colorPage.visible = false
                    palettePage.visible = false
                    settingsPage.visible = true
                    currentPage = text
                    drawer.close()
                }
            }
        }
    }

    DeviceManager {
        id: deviceMan


        onOnBLEStartedSearch: {
            homePage.searchIndicator.running = true
        }

        onOnBLEStoppedSearch: {
            homePage.searchIndicator.running = false
        }

        onOnBLEConnect: {
            homePage.connLabel.text = "Connected"
            homePage.connLabel.color = "#0099ff"
            homePage.connButton.text = "Disconnect"
        }

        onOnBLEReady: {
            homePage.connLabel.text = "Ready"
            homePage.connLabel.color = "#00aa00"
            homePage.connButton.text = "Disconnect"
        }

        onOnBLEConnecting: {
            homePage.connLabel.text = "Connecting..."
            homePage.connLabel.color = "#aaaa00"
        }

        onOnBLEDisconnect: {
            homePage.connLabel.text = "Disconnected"
            homePage.connLabel.color = "#ff0000"
            homePage.connButton.text = "Connect"
        }

        onOnBLEFault: {
            homePage.connLabel.text = "Err: "+errMsg
            homePage.connLabel.text = "Disconnected"
            homePage.connLabel.color = "#ff0000"
            homePage.connButton.text = "Connect"
        }
    }

    Home {
        id: homePage
        visible: true
        anchors.fill: parent
    }

    Palette {
        id: palettePage
        visible: false
        anchors.fill: parent
    }

    StaticColor {
        id: colorPage
        visible: false
        anchors.fill: parent
    }

    Settings {
        id: settingsPage
        visible: false
        anchors.fill: parent
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
