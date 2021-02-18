import QtQuick 2.4
import QtQuick.Controls.Material 2.12

SettingsForm {

    //Expose switch checked to main. If the theme is set from main, it will be set across the entire app.
    property bool darkMode: darkModeSwitch.checked

    //Also expose darkModeSwitch.checked to backend, that way it can be set from a saved config

    autoConnectSwitch {
        checked: false //Use backend property
        onCheckedChanged: {
            //Set backend property
        }
    }

}
