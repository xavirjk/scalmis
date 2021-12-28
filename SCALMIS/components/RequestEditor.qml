import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import components 1.0
import SCALMIS 1.0
Item {
    property Requests requests
    id :main
    ScrollView {
        width: main.width
        height: 500
        clip: true
        Column {
            id: col
            spacing: 3
            width:Math.floor(main.width)- 20
            Repeater {
                id: reqView
                width: col.width
                model: requests.ui_requests
                delegate: CRequestItem{
                    width: reqView.width
                    stockItem: modelData
                    onSetStates: requests.setmodels()
                    onRefresh: requests.requestsChanged()
                }
            }
            Rectangle {
                height: 10
                width: parent.width
            }
            Row {
                width: parent.width
                spacing: 10
                IconButton {
                    onIconBtnClicked:{requests.appendItem();}
                    displayText: "\uf067"
                }
                IconButton {
                    onIconBtnClicked: {requests.removeItem();}
                    displayText: "\uf068"
                }
            }
            CommandBar {
                commandList: masterController.ui_commander.ui_contextCommands
            }
        }
    }
}
