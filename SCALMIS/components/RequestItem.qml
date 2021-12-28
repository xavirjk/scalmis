import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import components 1.0
import SCALMIS 1.0
Item {
    property Requests requests: masterController.ui_requests
    Component.onCompleted: deleteModel()
    function deleteModel (){
        requests.ui_Officer.ui_input = ""
        requests.ui_Office.ui_input = ""
    }

    function getDt(){
        for(let i = 0; i < requests.ui_authsComboSelect.ui_combo.length; i++){
            if(requests.ui_authsComboSelect.ui_combo[i].ui_value ===
                    Number(requests.ui_Officer.ui_input)) return i
        }
        return  -1
    }
    Rectangle {
        id: rI
        anchors {
            top: parent.top
            bottom: parent.bottom
        }
        width: contentFrame.width
        anchors.margins: 10
        Column {
            spacing: 2
            width: parent.width-100
            Rectangle {
                width: parent.width;
                height: 35
                color: "#f0f0f0"
                StringEditor {
                    anchors.verticalCenter: parent.verticalCenter
                    textDesc: "Office Selection"
                }
            }
            Rectangle {
                width: parent.width
                height: 120
                radius: 3
                border.color: Style.defaulttxt_bg
                border.width: 2
                Row {
                    anchors.fill: parent
                    spacing: 2
                    anchors.margins: 3
                    Item {
                        id: selBox
                        width: parent.width*0.4
                        height: parent.height *0.6
                        Rectangle {
                            anchors{fill: parent;margins: 10}
                            ComboBox {
                                id: combo8;width: parent.width * 3/4;height: parent.height;textRole: "ui_key"
                                valueRole: "ui_value";currentIndex: -1
                                displayText: currentIndex === -1? 'specify officer':currentText
                                model: requests.ui_authsComboSelect.ui_combo
                                Component.onCompleted: currentIndex < 0?unreg.visible = true:unreg.visible = false
                                onActivated: function(){
                                    if(currentText !== requests.ui_Office.ui_input){
                                        requests.ui_Office.ui_input = currentText
                                        requests.ui_Officer.ui_input = ""
                                        requests.officeMembers();
                                        selBox2.visible = true;
                                        combo9.currentIndex = -1;

                                    }
                                    unreg.visible = false
                                }
                                font.pixelSize: 18;font.weight: Font.Medium;font.family: 'Impact, fantacy'
                            }

                        }
                    }
                    Item {id: selBox2;width: parent.width*0.4;height: parent.height *0.6;visible: false
                        Rectangle {anchors{fill: parent;margins: 10}
                            ComboBox {
                                id: combo9;width: parent.width * 3/4;height: parent.height;textRole: "ui_key"
                                valueRole: "ui_value";currentIndex: -1
                                displayText: currentIndex === -1? '..Select..':currentText
                                model: requests.ui_membersComboSelect.ui_combo
                                onActivated: if(currentValue !== requests.ui_Officer.ui_input){
                                                 requests.ui_Officer.ui_input = currentValue
                                             }
                                font.pixelSize: 18;font.weight: Font.Medium;font.family: 'Impact, fantacy'
                            }
                        }
                    }
                    Rectangle {
                        id: unreg
                        width: (parent.width - selBox.width) - 2
                        height: parent.height
                        Row {
                            anchors.fill: parent
                            spacing: 2
                            StringInput {
                                stringDecorator: requests.ui_Officer
                                cardHeight: 60
                                width: parent.width/2
                            }
                            StringInput {
                                stringDecorator: requests.ui_Office
                                cardHeight: 60
                                width: parent.width/2
                            }
                        }
                    }
                }
            }
            CommandBar {
                commandList: masterController.ui_commander.ui_contextCommands
            }
        }
    }
}
