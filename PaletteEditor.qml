import QtQuick 2.4

import StephenHamilton.SigmonLED.CustomPaletteEditor 1.0
import QtQuick.Controls 2.15

PaletteEditorForm {
    id: page

    property alias backend: backend
    //property alias saveButton: saveButton

    CustomPaletteEditorBackend {
        id: backend

        onNameChanged: nameField.text = name
    }

    gridView {
        model: PaletteEditorModel {
            list: backend.list
        }

        delegate: RoundButton {
            height: gridView.cellHeight
            width: gridView.cellWidth
            background: Rectangle {
                height: gridView.cellHeight / 4
                width: gridView.cellWidth / 4
                color: model.color
                radius: parent.radius
            }

            text: model.index
            font.pointSize: 17

            onClicked: {
                //Open color picker. When apply is clicked, set the palette color index
                console.log("Clicked on "+model.index)
            }
        }
    }
}
