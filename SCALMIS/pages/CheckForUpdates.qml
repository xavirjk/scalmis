import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import components 1.0
import SCALMIS 1.0
Item {
    Connections {
        target: masterController
        function onViewUpdates(data){
            if(!data.scalmis&&!data.server) {
                col.visible = false
                toDate.visible = true
            }
            else {
                if(data.scalmis){
                    scalmis.visible = true;
                    txt1.text = 'Downloading Scalmis Update version '+data.scalmis
                    masterController.ui_commander.downloadUpdate(0)
                }
                if(data.server && !data.scalmis){
                    server.visible = true;
                    txt2.text = 'Downloading Server Update version '+data.server
                    masterController.ui_commander.downloadUpdate(1)
                }
            }
        }
    }

    Component.onCompleted: function(){
        masterController.updates();
    }
    Rectangle {
        id: upd
        anchors {
            top: parent.top
            bottom: parent.bottom
        }
        width: contentFrame.width
        anchors.margins: 10
        Rectangle {
            id: toDate;width: parent.width -100; height: 100;visible: false
            Text {
                font.pixelSize: 20;text: 'No Updates Available'; id:updt
                font.family: 'consolas';verticalAlignment: Text.AlignVCenter
            }
        }

        Column {
            width: parent.width - 100;spacing: 2;id: col
            Rectangle {
                width: parent.width;height: 80;id: scalmis;visible: false
                Text {
                    font.pixelSize: 20;text: 'Update Scalmis'; id:txt1
                    font.family: 'consolas';verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                width: parent.width;height: 80; id: server;visible: false
                Text {
                    font.pixelSize: 20;text: 'Update Server';id:txt2
                    font.family: 'consolas';verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }
}
