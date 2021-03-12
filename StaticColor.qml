import QtQuick 2.0
import StephenHamilton.SigmonLED.ColorPicker 1.0
import StephenHamilton.SigmonLED.StaticColor 1.0

ColorPickerForm {
    id: page

    ColorPickerBackend {
        id: pickerBack
        onHueChanged: hueSlider.value = hue
        onSaturationChanged: satSlider.value = saturation
        onBrightnessChanged: valSlider.value = brightness
    }

    StaticColorBackend {
        id: staticBack
    }

    applyButton {
        onClicked: staticBack.apply(hueSlider.value, satSlider.value, valSlider.value)
    }

    hueSlider {
        onValueChanged: pickerBack.hue = hueSlider.value
    }

    satSlider {
        onValueChanged: pickerBack.saturation = satSlider.value
    }

    valSlider {
        onValueChanged: pickerBack.brightness = valSlider.value
    }

    Component.onCompleted: pickerBack.setSettingName("StaticColor")
    onVisibleChanged: {
        if(page.visible === false){
            pickerBack.saveSettings()
        }
    }
}
