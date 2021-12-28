import QtQuick 2.9
import SCALMIS 1.0
import assets 1.0
Item {
    property alias textDesc: textval.text
    property bool setH
    property string family:textval.font.family
    property int pixel:textval.font.pixelSize
    Text {
        id: textval
        anchors.fill: parent
        text: ''
        font.pixelSize: 18
        font.weight: Font.Medium
        font.family: 'serifs'
        horizontalAlignment: setH ? Text.AlignHCenter: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        color: '#e98f19'
    }

}
