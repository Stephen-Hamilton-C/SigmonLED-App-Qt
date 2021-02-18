import QtQuick 2.0
import QtQuick.Controls 2.5
import StephenHamilton.SigmonLED.Home 1.0

HomeForm {
    id: page

    HomeBackend {
        id: homeBack
    }

    connButton.onClicked: homeBack.connectPressed()
    showAllButton.onActivated: {
        homeBack.showAll = !homeBack.showAll
        showAllButton.text = homeBack.showAll ? "Hide" : "Show All"
    }

    devicesList {
        model: homeBack.devices
        delegate: ItemDelegate {
            required property string modelData
            width: 100
            anchors {
                left: parent.left
                right: parent.right
            }
            //Remove the encoded MAC address from the modelData
            text: modelData.substring(0, modelData.length-18)
            //Highlight if selected
            highlighted: homeBack.highlightedDelegate == modelData

            //select on click
            onClicked: homeBack.highlightedDelegate = modelData
        }
    }


}
