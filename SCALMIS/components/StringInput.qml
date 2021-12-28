import QtQuick 2.9
import components 1.0
import assets 1.0
import SCALMIS 1.0
Rectangle {
    property StringDecorator stringDecorator
    property int cardHeight
    property bool isPassword
    width: parent.width
    height: cardHeight

    Rectangle {
        height: Math.floor(cardHeight/2)
        width: parent.width
        Text {
            id: header
            anchors.fill: parent
            text: stringDecorator.ui_label
            font.pixelSize: 18
            verticalAlignment: Text.AlignBottom
            font.family: Style.defaultFontFamily
            color: Style.defaulttxt_bg

        }

        anchors.margins: 20
    }

    Rectangle {
        anchors.bottom: parent.bottom
        width: parent.width * 3/4
        height: Math.floor(cardHeight/2)
        CustomBorder {
            b_borderW: 3
            t_borderW: 0
            r_borderW: 0
            l_borderW: 0
            common_border: false
            borderColor: Style.defaulttxt_bg
        }
        TextInput {
            id: textVal
            anchors {
                fill: parent
                leftMargin: 10
                bottomMargin: 5
            }
            selectByMouse: true
            text: stringDecorator.ui_input
            verticalAlignment: Qt.AlignBottom
            font.pixelSize: 16
            echoMode: isPassword? TextInput.Password : TextInput.Normal
        }
        Binding {
            target:stringDecorator
            property: "ui_input"
            value: textVal.text
        }
    }
}