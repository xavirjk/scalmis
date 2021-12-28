import QtQuick 2.9
import assets 1.0

Item {
    property alias iconChar: textIcon.text
    property alias description: textDescription.text

    signal navBtnClicked();
    height: Style.navbarElHeight
    width: parent.width
     Rectangle {
            id: bc_ground
            anchors {
                fill: parent;
                margins: 10
            }
            Row {
                anchors.fill: parent
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
                    verticalAlignment: Text.AlignVCenter

                }
                Text {
                    id: textDescription
                    text: ''
                    width: parent.width * 3/4
                    height: parent.height
                    font.pixelSize: 16
                    font.family: 'Impact, fantacy'
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

}
