import QtQuick 2.4
import QtQuick.Controls.Material 2.12
import StephenHamilton.SigmonLED.Settings 1.0

SettingsForm {

    //Expose switch checked to main. If the theme is set from main, it will be set across the entire app.
    property bool darkMode: darkModeSwitch.checked

    //Also expose darkModeSwitch.checked to backend, that way it can be set from a saved config
    SettingsBackend {
        id: backend

        onDarkModeChanged: darkModeSwitch.checked = darkMode
        onAutoConnectChanged: autoConnectSwitch.checked = autoConnect
    }

    darkModeSwitch {
        onCheckedChanged: {
            backend.darkMode = darkModeSwitch.checked
        }
    }

    autoConnectSwitch {
        onCheckedChanged: {
            backend.autoConnect = autoConnectSwitch.checked
        }
    }

}
