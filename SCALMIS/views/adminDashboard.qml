import QtQuick 2.9
import assets 1.0
import QtQuick.Controls 2.2
Item {
    Rectangle {
        anchors.fill: parent
        Text {
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: 'Impact, Fantacy'
            id: pageDesc
            text: 'Admin DashBoard'
            font.pixelSize: Style.pixelSizeFirm

        }
    }
}
