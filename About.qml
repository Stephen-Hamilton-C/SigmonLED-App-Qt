import QtQuick 2.15

AboutForm {
    id: page

    versionLabel.text: 'SigmonLED - ' + Qt.application.version
    aboutLabel.onLinkActivated: Qt.openUrlExternally(link)
}
