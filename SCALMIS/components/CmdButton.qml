import QtQuick 2.9
import SCALMIS 1.0
import assets 1.0
Rectangle {
    property Commands commands
    id: submitBtn
    width: 150
    height:parent.height
    anchors.margins: 10
    color: "grey"
    radius: 5
    Text {
        id: textFl
        anchors.fill: parent
        anchors.margins: 5
        font.family: 'consolas'
        text: commands.ui_canExecute ? commands.ui_text: '...'
        font.pixelSize: 22
        font.weight: Font.Bold
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onEntered:submitBtn.state = "hover"
        onExited:submitBtn.state = ""
        onClicked:if(commands.ui_canExecute){
                      commands.execute()
                  }
    }
    states: [
        State {
            name: "hover"
            PropertyChanges {
                target: submitBtn
                color: Style.defaulttxt_bg
            }
            PropertyChanges {
                target: textFl
                color: 'white'
            }
        }
    ]
}
