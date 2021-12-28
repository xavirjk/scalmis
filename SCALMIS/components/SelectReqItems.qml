import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import components 1.0
import SCALMIS 1.0
Item {
    property Requests newRequests: masterController.ui_requests
    Rectangle {
        id: req
        anchors {
            top: parent.top
            bottom: parent.bottom
        }
        width: contentFrame.width
        anchors.margins: 10
            Rectangle {
                id: bar
                width:parent.width -100
                height: 35
                color: "#f0f0f0"
                StringEditor {
                    anchors.verticalCenter: parent.verticalCenter
                    textDesc: "Item Selection"
                }
            }
            RequestEditor {
                anchors {
                    top: bar.bottom
                    left: parent.left
                }
                requests: newRequests
                width: bar.width
            }
    }
}
