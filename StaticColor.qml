import QtQuick 2.0
import StephenHamilton.SigmonLED.StaticColor 1.0

StaticColorForm {
    id: page

    StaticColorBackend {
        id: colorBack
    }

    applyButton {
        onClicked: colorBack.Apply()
    }

    hueSlider {
        onValueChanged: colorBack.setH(hueSlider.value)
    }

    satSlider {
        onValueChanged: colorBack.setS(satSlider.value)
    }

    valSlider {
        onValueChanged: colorBack.setV(valSlider.value)
    }

}
