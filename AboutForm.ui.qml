import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: 450
    height: 800
    property alias aboutLabel: aboutLabel
    property alias versionLabel: versionLabel

    Page {
        id: page
        anchors.fill: parent
        title: "About"

        Image {
            id: logo
            x: 127
            width: 200
            height: 200
            anchors.top: parent.top
            source: "icons/SigmonLED Icon.png"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 18
            fillMode: Image.PreserveAspectFit
        }

        Label {
            id: versionLabel
            text: qsTr("SigmonLED - VERSION")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: logo.bottom
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            anchors.leftMargin: 18
            anchors.rightMargin: 18
            font.pointSize: 16
            anchors.topMargin: 18
        }

        Label {
            id: arduinoLabel
            text: qsTr("Supports SigmonLED-Arduino 0.3 and above")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: versionLabel.bottom
            horizontalAlignment: Text.AlignHCenter
            anchors.topMargin: 6
            anchors.rightMargin: 18
            anchors.leftMargin: 18
            font.bold: false
            font.pointSize: 12
        }

        Label {
            id: aboutLabel
            text: "SigmonLED allows you to control a SigmonLED powered Arduino with your Android device - no terminal commands necessary!<br><br>The Arduino code can be found <a href=\"https://github.com/Stephen-Hamilton-C/SigmonLED-Arduino\">on Github</a>.<br><br>SigmonLED is an open source project developed by a college student for his sister. The source code can be found <a href=\"https://github.com/Stephen-Hamilton-C/SigmonLED-App\">here.</a>\n\n<br><br>SigmonLED is licensed under the <a href=\"https://www.gnu.org/licenses/gpl-3.0.en.html\">GNU General Public License v3.0</a>."
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: arduinoLabel.bottom
            anchors.bottom: parent.bottom
            wrapMode: Text.WordWrap
            font.pointSize: 16
            anchors.rightMargin: 18
            anchors.leftMargin: 18
            anchors.bottomMargin: 18
            anchors.topMargin: 18
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:3}D{i:4}
}
##^##*/

