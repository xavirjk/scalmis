import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import components 1.0
import SCALMIS 1.0
Rectangle {
    property Requests requests
    id: main
    ScrollView {
        width: main.width -100
        height: 500
        clip: true
        Column {
            id: col
            spacing: 3
            width:Math.floor(main.width)-120
            Repeater {
                id: serviceView
                width: col.width
                model: requests.ui_srvrequests
                delegate: CRequestService{
                    width: serviceView.width
                    service: modelData
                    onSetStates: requests.setServiceModels()
                    onRefresh: requests.srvRequestsChanged()
                }
            }
            Rectangle {
                height: 10
                width: parent.width
            }
            Row {
                visible: true
                id: actionBar
                width: parent.width
                spacing: 10
                IconButton {
                    onIconBtnClicked: requests.appendService()
                    displayText: "\uf067"
                }
                IconButton {
                    onIconBtnClicked: requests.removeService()
                    displayText: "\uf068"
                }
            }
            CommandBar {
                commandList: masterController.ui_commander.ui_contextCommands
            }
        }
    }
}
