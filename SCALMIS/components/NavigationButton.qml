import QtQuick 2.9
import assets 1.0

Item {
    property alias iconChar: textIcon.text
    property alias description: textDescription.text
    property alias setH:button.height
    property alias setP:textIcon.font.pixelSize
    property alias setICW: textIcon.width
    property alias setTPW: textDescription.width
    property alias setTP:textDescription.font.pixelSize
    property bool hideHoverbcg
    property bool topCenterAlign
    property bool noMargins
    property bool noHoverMargins
    id: button
    signal navBtnClicked();
    width: parent.width
     Rectangle {
            id: bc_ground
            anchors {
                fill: parent;
                margins: noMargins?0:10
            }
            Row {
                anchors.fill: parent
                anchors.leftMargin: 3
                Text{
                    id: textIcon
                    width: parent.width/4
                    color: Style.defaulttxt_bg
                    height: parent.height
                    text: ''
                    font {
                        family: Style.fontAwesome
                        pixelSize: 30
                    }
                    horizontalAlignment: topCenterAlign ? Text.AlignHCenter: Text.AlignLeft
                    verticalAlignment: topCenterAlign? Text.AlignTop: Text.AlignVCenter
                }
                Text {
                    id: textDescription
                    text: ''
                    width: parent.width * 3/4
                    height: parent.height
                    font.pixelSize: 16
                    font.family: 'Impact, fantacy'
                    horizontalAlignment: topCenterAlign ? Text.AlignHCenter: Text.AlignLeft
                    verticalAlignment: topCenterAlign? Text.AlignTop: Text.AlignVCenter
                }
            }
            states: [
                State {
                    name: "hover"
                    PropertyChanges {
                        target: bc_ground
                        color: hideHoverbcg?'transparent':'lightgray'
                        anchors.margins: noMargins? 0: 5
                    }
                }

            ]
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onEntered:bc_ground.state = 'hover'
                onExited: bc_ground.state = ''
                onClicked: navBtnClicked()
            }

        }

}
