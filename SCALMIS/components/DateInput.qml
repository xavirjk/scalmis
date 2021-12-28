import QtQuick 2.9
import components 1.0
import assets 1.0
import SCALMIS 1.0
Rectangle {
    property DateTimeDecorator dateTimeDecorator
    property int cardHeight
    width: parent.width
    height: cardHeight

    Rectangle {
        height: Math.floor(cardHeight/2)
        width: parent.width
        Text {
            id: header
            anchors.fill: parent
            text: dateTimeDecorator.ui_label
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
            text: dateTimeDecorator.ui_input
            //text: new Date().toLocaleDateString();
            verticalAlignment: Qt.AlignBottom

        }
        Binding {
            target:dateTimeDecorator
            property: "ui_input"
            value:textVal.text
        }
    }
}
