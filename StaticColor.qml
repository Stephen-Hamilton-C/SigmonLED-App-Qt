import QtQuick 2.0
import StephenHamilton.SigmonLED.ColorPicker 1.0
import StephenHamilton.SigmonLED.StaticColor 1.0

ColorPickerForm {
    id: page

    StaticColorBackend {
        id: staticBack
    }

    ColorPicker {
        id: picker
        applyButton.onClicked: {
            staticBack.apply(hueSlider.value, satSlider.value, valSlider.value)
        }

        hueSlider.onValueChanged: {
            staticBack.hueChanged(hueSlider.value)
        }

        satSlider.onValueChanged: {
            staticBack.satChanged(satSlider.value)
        }

        valSlider.onValueChanged: {
            staticBack.valChanged(valSlider.value)
        }
    }

    Component.onCompleted: picker.pickerBack.setSettingName("StaticColor")

    onVisibleChanged: {
        if(page.visible === false){
            pickerBack.saveSettings()
        }
    }
}
