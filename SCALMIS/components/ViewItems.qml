import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import components 1.0
import SCALMIS 1.0
Item {
    property var anArray: []
    function getSelected(id, type) {
        for(let i = 0; i < anArray.length; i++){
            if(anArray[i]._id === id){
                var arr = [];
                arr.push(anArray[i]);
               return masterController.ui_commander.setUpStockItems(arr,type)
            }
        }
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
                textDesc: "Selected Stock Items:"
            }
        }
        Row {
            id: row
            width: parent.width -100
            height: 30
            spacing: 10
            anchors {
                topMargin: 5
                leftMargin: 15
                left: parent.left
                top: dd.bottom
            }
            Rectangle {
                id: itemBox
                width: parent.width*0.15
                height: parent.height
                color: "green"
                StringEditor {
                    anchors.fill: parent
                    textDesc: "Item"
                    setH: true
                }

            }
            Rectangle {
                id:descBox
                width: parent.width*0.2
                height: parent.height
                color: "green"
                StringEditor {
                    anchors.fill: parent
                    textDesc: "Description"
                    setH: true
                }
            }
            Rectangle {
                id:quantBox
                width: parent.width*0.1
                height: parent.height
                color: "green"
                StringEditor {
                    anchors.fill: parent
                    textDesc: "Quantity"
                    setH: true
                }
            }
            Rectangle {
                id:actionBox
                width: parent.width*0.45
                height: parent.height
                color: "green"
                StringEditor {
                    anchors.fill: parent
                    textDesc: "Action"
                    setH: true
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
                width: parent.width
                spacing: 2
                id:col
                Repeater {
                    model: anArray
                    Rectangle {
                        width: dd.width - 24.5
                        height: 45
                        Rectangle {
                            id: div
                            width: parent.width - 20
                            height: parent.height
                            anchors.right: parent.right
                            anchors.margins: 5
                            color: "#f0f0f0"
                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor
                                onEntered:div.state = "hover"
                                onExited: div.state = ""
                                Row {
                                    anchors.centerIn: parent
                                    anchors.leftMargin: 1
                                    width: parent.width - 2
                                    spacing: 10
                                    height: parent.height-10
                                    Rectangle {width: itemBox.width;color: 'transparent';height: parent.height
                                        Text {
                                            anchors.fill: parent
                                            font.pixelSize: 15
                                            text: modelData.item
                                            verticalAlignment: Text.AlignVCenter
                                            horizontalAlignment: Text.AlignLeft
                                            anchors.leftMargin: 10
                                        }
                                    }
                                    Rectangle {
                                        width: descBox.width;height: parent.height;color: 'transparent'
                                        Text {
                                            anchors.fill: parent
                                            font.pixelSize: 15
                                            text: modelData.description
                                            verticalAlignment: Text.AlignVCenter
                                            horizontalAlignment: Text.AlignLeft
                                            anchors.leftMargin: 10
                                        }
                                    }
                                    Rectangle {
                                        width: quantBox.width;height: parent.height;color: 'transparent'
                                        Text {
                                            anchors.fill: parent
                                            font.pixelSize: 15
                                            text: modelData.amountAdded
                                            verticalAlignment: Text.AlignVCenter
                                            horizontalAlignment: Text.AlignLeft
                                            anchors.leftMargin: 10
                                        }
                                    }
                                    Rectangle {id:actionbar;visible: false;width: actionBox.width;height: parent.height;color:'transparent'
                                        Row {
                                            spacing: 30
                                            IconButton {displayText:"\uf06e";onIconBtnClicked: getSelected(modelData._id, "item edit")}
                                            IconButton{displayText: '\uf304'; onIconBtnClicked: getSelected(modelData._id, "item update")}
                                        }
                                    }
                                }
                            }
                            states: [State {name: "hover"
                                    PropertyChanges{target: actionbar;visible: true}
                                }
                            ]
                        }
                    }
                }
            }
        }
    }
}
