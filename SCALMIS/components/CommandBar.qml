import QtQuick 2.9
import SCALMIS 1.0
import assets 1.0
Item {
    property alias commandList: commandRepeater.model
    width: parent.width
    height: 60
    Rectangle {
        anchors.fill: parent
        Row {
            anchors.fill: parent
            spacing: 300
            Repeater {
                id: commandRepeater
                delegate: CmdButton {
                    commands: modelData
                }
            }
        }
    }
}
