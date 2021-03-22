import QtQuick 2.0
import StephenHamilton.SigmonLED.Palette 1.0

PaletteForm {
    id: page

    PaletteBackend {
        id: paletteBack

        //TODO: fix text not updating. Not allowed to set currentText
        onPaletteChanged: paletteBox.currentText = palette
        onDelayChanged: delayBox.value = delay
        onBrightnessChanged: brightnessSlider.value = brightness
        onSolidPaletteChanged: solidPaletteSwitch.checked = solidPalette
        onLinearBlendingChanged: linearBlendSwitch.checked = linearBlending
    }

    brightnessSlider {
        onValueChanged: paletteBack.setBrightness(brightnessSlider.value)
    }

    delayBox {
        onValueChanged: paletteBack.setDelay(delayBox.value)
    }

    solidPaletteSwitch {
        onCheckedChanged: paletteBack.setSolidPalette(solidPaletteSwitch.checked);
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

    testButton.onClicked: paletteBack.testCustomPalette()

}
