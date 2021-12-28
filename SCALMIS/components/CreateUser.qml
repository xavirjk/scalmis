import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import components 1.0
import SCALMIS 1.0
Item {
    property Accounts newUser: masterController.ui_accounts
    Component.onCompleted: function(){
        if(masterController.ui_commander.getContext() === "Change-password")
        {pass.visible = true;email.visible=false;office.visible=false;pjno.visible=false;fname.visible=false}
    }

    Rectangle {
        id: nS
        anchors {
            top: parent.top
            bottom: parent.bottom
        }
        width: contentFrame.width
        anchors.margins: 10
        Rectangle {
            width: parent.width - 100
            height: 500
            Rectangle {
                id: bar
                width: parent.width;
                height: 35
                color: "#f0f0f0"
                StringEditor {
                    anchors.verticalCenter: parent.verticalCenter
                    textDesc: masterController.ui_commander.getContext()
                }
            }
            Rectangle {
                width: parent.width
                anchors {
                    top: bar.bottom
                    left: parent.left
                    bottom: parent.bottom
                    leftMargin: width*0.15
                    topMargin: 20
                }
                Rectangle {
                    width: parent.width *0.75
                    border.width: 2
                    border.color: "#f0f0f0"
                    radius: 3
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    Column {
                        width: parent.width -10
                        spacing: 10
                        Item {
                            width: parent.width * 0.7
                            height: 40
                            Rectangle {
                                anchors.fill: parent
                                ComboBox {
                                    id: combo
                                    width: parent.width * 0.4
                                    height: parent.height *0.8
                                    textRole: "ui_key"
                                    valueRole: "ui_value"
                                    currentIndex: -1
                                    displayText: currentIndex === -1? "Select Auth Type": currentText
                                    model: newUser.ui_typeCombo.ui_combo
                                    onActivated: newUser.ui_type.ui_input = currentValue
                                }

                            }
                        }
                        IntInput {
                            intDecorator: newUser.ui_pjno
                            cardHeight: 70;id:pjno
                            width: parent.width
                        }
                        StringInput {
                            stringDecorator: newUser.ui_fullname
                            cardHeight: 70;id:fname
                            width: parent.width
                        }
                        StringInput {
                            stringDecorator: newUser.ui_office
                            cardHeight: 70;id:office
                            width: parent.width
                        }
                        StringInput {
                            id:pass;visible: false
                            stringDecorator: newUser.ui_password
                            cardHeight: 70
                            width: parent.width
                        }

                        StringInput {
                            stringDecorator: newUser.ui_email
                            cardHeight: 70;id:email
                            width: parent.width
                        }
                        CommandBar {
                            commandList: masterController.ui_commander.ui_contextCommands
                        }
                    }
                }


            }
        }
    }
}
