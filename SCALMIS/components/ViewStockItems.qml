import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import components 1.0
import SCALMIS 1.0
Item {
    property Requests requests: masterController.ui_requests
    property string type: ''
    function headerText(){
        if(type === 'all') return 'STOCK ITEMS'
        else return 'Items '+type;
    }
    function getReq(mark){
        let array = [];
        let combo = requests.ui_itemsComboSelect.ui_combo.length;
        for(let i = 0 ; i < combo; i++){
            if(requests.ui_itemsComboSelect.ui_combo[i].ui_value <= mark)
                array.push(requests.ui_itemsComboSelect.ui_combo[i])
        }
        return array;
    }

    function displayModel(){
        if(type === 'all') {
            return requests.ui_itemsComboSelect.ui_combo
        }
        else if(type === 'onDepletion') return getReq(10)
        else return getReq(0)
    }

    Rectangle {
        id: vS
        anchors {
            top: parent.top
            bottom: parent.bottom
        }
        width: contentFrame.width
        anchors.margins: 10
        Rectangle {
            id: dd
            width: parent.width - 100;
            height: 35
            color: "#f0f0f0"
            StringEditor {
                anchors.verticalCenter: parent.verticalCenter
                textDesc: headerText()
            }
        }
        Row {
            id: row
            width: parent.width * 0.52
            height: 40
            spacing: 10
            anchors {
                topMargin: 5
                leftMargin: 15
                left: parent.left
                top: dd.bottom
            }
            Rectangle {
                width: parent.width
                height: parent.height
                color: 'green'
                Rectangle {
                    id:itemsHeader
                    width: parent.width*0.3
                    height: parent.height
                    color: 'transparent'
                    StringEditor {
                        anchors.fill: parent
                        textDesc: "ITEM"
                        setH: true
                        pixel: 30
                        family: 'Arial Bold'
                    }
                }
                Rectangle {
                    anchors.left: itemsHeader.right
                    width: itemsHeader.width
                    height: parent.height
                    color: 'transparent'
                    StringEditor {
                        anchors.fill: parent
                        textDesc: "QUANTITY"
                        setH: true;pixel: 30
                        family: 'Arial Bold'
                    }
                }
            }
        }
        ScrollView {
            anchors.top: row.bottom
            anchors.margins: 10
            width: parent.width -100
            height: 500
            clip: true
            Column {
                width: row.width + 50
                spacing: 10
                id:col
                Repeater {
                    model: displayModel()
                    Column {
                        //width: dd.width - 24.5
                        width: dd.width * 0.6
                        spacing: 1
                        Rectangle {
                            width: parent.width
                            height: 50
                            Rectangle {
                                id: div
                                width: parent.width - 20
                                height: parent.height
                                anchors.right: parent.right
                                anchors.margins: 5
                                color: '#f0f0f0'
                                radius: 2
                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                    onEntered:div.state = "hover"
                                    onExited: div.state = ""
                                    onClicked: {
                                        masterController.ui_commander.cBoxDesc(modelData.ui_key)
                                        requests.ui_toggle.ui_input = 0;
                                        col2.visible = true
                                    }

                                    Row {
                                        anchors.centerIn: parent
                                        anchors.leftMargin: 1
                                        width: parent.width - 2
                                        spacing: 10
                                        height: parent.height-10
                                        Rectangle {
                                            width: itemsHeader.width
                                            height: parent.height
                                            color: 'transparent'
                                            Text {
                                                anchors.fill: parent
                                                font.pixelSize: 15
                                                text: modelData.ui_key
                                                verticalAlignment: Text.AlignVCenter
                                                horizontalAlignment: Text.AlignLeft
                                                anchors.leftMargin: 10
                                            }
                                        }
                                        Rectangle {
                                            width: itemsHeader.width
                                            height: parent.height
                                            color: 'transparent'
                                            Text {
                                                anchors.fill: parent
                                                font.pixelSize: 15
                                                text: modelData.ui_value
                                                verticalAlignment: Text.AlignVCenter
                                                horizontalAlignment: Text.AlignLeft
                                                anchors.leftMargin: 10
                                            }
                                        }
                                        Rectangle {
                                            id:actionbar
                                            width: 80
                                            color: 'transparent'
                                            height: parent.height
                                        }
                                    }
                                }
                            }
                        }
                   }
                }
            }
            Column {
                id: col2
                spacing: 2
                anchors {
                    left: col.right
                    right: parent.right
                }
                Repeater {
                    model: requests.ui_descComboSelect.ui_combo
                    Column {
                        id: model2
                        width: parent.width
                        spacing: 2
                        Rectangle {
                            color: 'green'
                            width:parent.width -5;height: 20;
                            Rectangle {
                                width: parent.width - 15.5;height: parent.height
                                anchors.right: parent.right
                                Row{
                                    width: parent.width;spacing: 4;height: parent.height
                                    Rectangle {
                                        width: itemsHeader.width
                                        height: parent.height
                                        Text {
                                            anchors.fill: parent
                                            font.pixelSize: 15
                                            text: modelData.ui_key
                                            verticalAlignment: Text.AlignVCenter
                                            horizontalAlignment: Text.AlignLeft
                                            anchors.leftMargin: 10
                                        }
                                    }
                                    Rectangle {
                                        width: itemsHeader.width
                                        height: parent.height
                                        Text {
                                            anchors.fill: parent
                                            font.pixelSize: 15
                                            text:modelData.ui_value
                                            verticalAlignment: Text.AlignVCenter
                                            horizontalAlignment: Text.AlignLeft
                                            anchors.leftMargin: 10
                                        }
                                    }
                                }
                            }
                        }
                    }
               }
            }
        }
    }
}
