import QtQuick 2.9
import assets 1.0

Item {
    property alias displayText: btnText.text
    signal actionBtnClicked();
    height: 100
    width: parent.width
    Rectangle {
        id: actionBtn
        anchors.margins: 10
        anchors.bottom: parent.bottom
        height: 50
        width: 150
        color: Style.defaulttxt_bg
        radius: 5
        Text {
            anchors.fill: parent
            id: btnText
            text: "text"
            font.pixelSize: 18
            font.family: "Impact, fantacy"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onEntered:actionBtn.state = "hover"
            onExited: actionBtn.state = ""
            onClicked:actionBtnClicked()
        }
        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: actionBtn
                    height:55
                    width: 155

                }
            }
        ]
    }

}
