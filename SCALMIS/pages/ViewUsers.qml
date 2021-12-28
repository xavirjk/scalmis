import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import components 1.0
import SCALMIS 1.0
Item {
    property var anArray: []
    Rectangle {
        width: contentFrame.width;anchors.margins: 10
        anchors {top: parent.top;bottom: parent.bottom}
        Rectangle {
            id:dd;width: parent.width -100;height: 35;color: "#f0f0f0"
            StringEditor {anchors.verticalCenter: parent.verticalCenter;textDesc: "System Users"}
        }
        Row {
            id: row;width: parent.width -100;height: 30;spacing: 10
            anchors {topMargin: 5;leftMargin: 15;left: parent.left;top: dd.bottom}
            Rectangle {
                id: typeBox;width: parent.width*0.14;height: parent.height;color: "green"
                StringEditor {anchors.fill: parent;textDesc: "Type";setH: true}
            }
            Rectangle {
                id: officeBox;width: parent.width*0.18;height: parent.height;color: "green"
                StringEditor {anchors.fill: parent;textDesc: "Office";setH: true}
            }
            Rectangle {
                id:idBox;width: parent.width*0.18;height: parent.height;color: "green"
                StringEditor {anchors.fill: parent;textDesc: "Officer Identity";setH: true}
            }
            Rectangle {
                id:pjBox;width: parent.width*0.12;height: parent.height;color: "green"
                StringEditor {anchors.fill: parent;textDesc: "PjNo";setH: true}
            }
            Rectangle {
                id:actionBox;width: parent.width*0.29;height: parent.height;color: "green"
                StringEditor {anchors.fill: parent;textDesc: "Action";setH: true}
            }

        }
        ScrollView {
            anchors.top: row.bottom;anchors.margins: 10;width: parent.width -100;height: 450;clip: true
            Column {spacing: 4;width: parent.width;id:col
                Repeater {model: anArray
                    Rectangle {width: dd.width-24.5;height: 50
                        Rectangle {id: div;width: parent.width - 20;height: parent.height
                            anchors.right: parent.right;anchors.margins: 5;color: "#f0f0f0";radius: 2
                            Row{anchors.centerIn: parent;anchors.leftMargin: 1;width: parent.width - 2
                                spacing: 10;height: parent.height-10
                                Rectangle {width: typeBox.width;height: parent.height;color: 'transparent'
                                    Text {anchors.fill: parent;font.pixelSize: 15;anchors.leftMargin: 10
                                        text: modelData.__t;verticalAlignment: Text.AlignVCenter;horizontalAlignment: Text.AlignLeft
                                    }
                                }
                                Rectangle {width: officeBox.width;height: parent.height;color: 'transparent'
                                    Text {anchors.fill: parent;font.pixelSize: 15;anchors.leftMargin: 10
                                        text: modelData.office;verticalAlignment: Text.AlignVCenter;horizontalAlignment: Text.AlignLeft
                                    }
                                }
                                Rectangle {width: idBox.width;height: parent.height;color: 'transparent'
                                    Text {anchors.fill: parent;font.pixelSize: 15;anchors.leftMargin: 10
                                        text: modelData.fullName;verticalAlignment: Text.AlignVCenter;horizontalAlignment: Text.AlignLeft
                                    }
                                }
                                Rectangle {width: pjBox.width;height: parent.height;color: 'transparent'
                                    Text {anchors.fill: parent;font.pixelSize: 15;anchors.leftMargin: 10
                                        text: modelData.pjno;verticalAlignment: Text.AlignVCenter;horizontalAlignment: Text.AlignLeft
                                    }
                                }
                                Rectangle {width: actionBox.width;height: parent.height;color: 'transparent'
                                    Row{spacing: 20
                                    IconButton{displayText: '\uf2ed'; onIconBtnClicked: masterController.ui_commander.editUser(modelData, true)}
                                    IconButton{displayText: '\uf304'; onIconBtnClicked: masterController.ui_commander.editUser(modelData, false)}
                                    IconButton{displayText: '\uf084'; onIconBtnClicked: masterController.ui_commander.changePassword(modelData)}
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
