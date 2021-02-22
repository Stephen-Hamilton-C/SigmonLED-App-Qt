import QtQuick 2.0
import StephenHamilton.SigmonLED.Palette 1.0

PaletteForm {
    id: page

    PaletteBackend {
        id: paletteBack
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
