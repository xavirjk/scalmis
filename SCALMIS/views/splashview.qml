import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
Item {
    Rectangle {
        anchors.fill: parent
        color: Style.color_bg
        Text {
            id: splash
            anchors {
                centerIn: parent
            }
            font.pixelSize: Style.pixelSizeSplashView
            font.underline: true
            color: Style.defaulttxt_bg
            font.family: Style.defaultFontFamily
            text: qsTr("Splash View")
        }
    }
}
