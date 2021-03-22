import QtQuick 2.4
import QtQuick.Controls 2.15
import StephenHamilton.SigmonLED.CustomPalettes 1.0

CustomPalettesForm {
    id: page

    property bool deviceReady: false

    CustomPalettesBackend {
        id: backend
    }

    createButton.onClicked: backend.newPalette()

    listView {
        //model: backend.palettes
        /*
        model: ListModel {
            ListElement {
                name: "American Palette"
                uuid: "{129338946}"
                colors: [
                    ListElement {
                        color: "#ff0000"
                    },
                    ListElement {
                        color: "#666666"
                    },
                    ListElement {
                        color: "#0000ff"
                    }
                ]
            }
            ListElement {
                name: "Italian Palette"
                uuid: "{876249453}"
                colors: [
                    ListElement {
                        color: "#ff0000"
                    },
                    ListElement {
                        color: "#666666"
                    },
                    ListElement {
                        color: "#00ff00"
                    }
                ]
            }
        }
        */

        model: PaletteModel {
            list: backend.list
        }

        delegate: Item {
            //property list colors
            //required property string name
            //required property string id
            //x: 5
            //width: 80
            height: 50
            anchors.left: parent.left
            anchors.right: parent.right
            Item {
                id: row1
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                //spacing: 10
                Rectangle {
                    id: colorRect
                    width: 40
                    height: 40
                    gradient: Gradient {
                        GradientStop { position: 0.0 / 15.0; color: model.colors[0] }
                        GradientStop { position: 1.0 / 15.0; color: model.colors[1] }
                        GradientStop { position: 2.0 / 15.0; color: model.colors[2] }
                        GradientStop { position: 3.0 / 15.0; color: model.colors[3] }
                        GradientStop { position: 4.0 / 15.0; color: model.colors[4] }
                        GradientStop { position: 5.0 / 15.0; color: model.colors[5] }
                        GradientStop { position: 6.0 / 15.0; color: model.colors[6] }
                        GradientStop { position: 7.0 / 15.0; color: model.colors[7] }
                        GradientStop { position: 8.0 / 15.0; color: model.colors[8] }
                        GradientStop { position: 9.0 / 15.0; color: model.colors[9] }
                        GradientStop { position: 10.0 / 15.0; color: model.colors[10] }
                        GradientStop { position: 11.0 / 15.0; color: model.colors[11] }
                        GradientStop { position: 12.0 / 15.0; color: model.colors[12] }
                        GradientStop { position: 13.0 / 15.0; color: model.colors[13] }
                        GradientStop { position: 14.0 / 15.0; color: model.colors[14] }
                        GradientStop { position: 15.0 / 15.0; color: model.colors[15] }
                    }
                }

                Label {
                    text: model.name
                    anchors.verticalCenter: colorRect.verticalCenter
                    anchors.left: colorRect.right
                    anchors.leftMargin: 15
                    font.bold: true
                }

                Button {
                    id: uploadButton
                    enabled: deviceReady
                    text: "U"
                    anchors.right: editButton.left
                    anchors.rightMargin: 10
                    width: 40
                    height: 40
                    onClicked: backend.uploadPalette(model.uuid)
                }

                Button {
                    id: editButton
                    text: "E"
                    anchors.right: delButton.left
                    anchors.rightMargin: 10
                    width: 40
                    height: 40
                    onClicked: console.log("model: "+model)
                }

                Button {
                    id: delButton
                    text: "D"
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    width: 40
                    height: 40
                    onClicked: backend.delPalette(model.uuid)
                }
            }
        }
        /*
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
        */
    }
}
