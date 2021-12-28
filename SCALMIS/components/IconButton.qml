import QtQuick 2.9
import assets 1.0

Item {
    property alias displayText: btnText.text
    signal iconBtnClicked();
    height: 30
    width: 50
    Rectangle {
        id: iconBtn
        anchors.margins: 10
        height: parent.height
        width: 30
        color: Style.defaulttxt_bg
        radius: 5
        Text {
            anchors.fill: parent
            id: btnText
            text: "text"
            font.pixelSize: 20
            font.family: Style.fontAwesome
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onEntered:iconBtn.state = "hover"
            onExited: iconBtn.state = ""
            onClicked:iconBtnClicked()
        }
        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: iconBtn
                    color: "green"
                    width: 35

                }
            }
        ]
    }

}
