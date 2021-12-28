import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import components 1.0
import SCALMIS 1.0
Item {
    property var anArray: []
    function getLocalDateString(timeString){
        const date = new Date(timeString);
        return date.toLocaleString()
    }

    Rectangle {
        id: aS
        anchors {
            top: parent.top
            bottom: parent.bottom
        }
        width: contentFrame.width
        anchors.margins: 10
        Rectangle {
            id:dd
            width: parent.width -100;
            height: 35
            color: "#f0f0f0"
            StringEditor {
                anchors.verticalCenter: parent.verticalCenter
                textDesc: "Stock Created As At:"
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
                id: timeBox
                width: parent.width*0.4
                height: parent.height
                color: "green"
                StringEditor {
                    anchors.fill: parent
                    textDesc: "Date-Time Created"
                    setH: true
                }

            }
            Rectangle {
                id:actionBox
                width: parent.width*0.53
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
                        height: 40
                        Rectangle {
                            id: div
                            width: parent.width - 20
                            height: parent.height
                            anchors.right: parent.right
                            anchors.margins: 5
                            border{
                                width: 1
                                color: 'green'
                            }
                            radius: 2
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
                                    Rectangle {
                                        width: timeBox.width
                                        height: parent.height
                                        Text {
                                            anchors.fill: parent
                                            font.pixelSize: 15
                                            text: getLocalDateString(modelData.timecreated)
                                            verticalAlignment: Text.AlignVCenter
                                            horizontalAlignment: Text.AlignLeft
                                            anchors.leftMargin: 10
                                        }
                                    }
                                    Rectangle {
                                        id:actionbar
                                        visible: false
                                        width: actionBox.width
                                        height: parent.height
                                        Row {
                                            anchors{
                                                fill: parent
                                                topMargin: 3
                                            }
                                            spacing: 3
                                            Rectangle {
                                                width: 100
                                                height: parent.height
                                                IconButton {
                                                    onIconBtnClicked: masterController.ui_commander.getStockData(modelData._id)
                                                    anchors.centerIn: parent
                                                    displayText:"\uf06e"

                                                }
                                                Text {
                                                    anchors.right: parent.right
                                                     width: parent.width/2
                                                     height: parent.height
                                                     font.pixelSize: 15
                                                     text:"View"
                                                     horizontalAlignment: Text.AlignRight
                                                     verticalAlignment: Text.AlignVCenter
                                                }
                                            }
                                            /*Rectangle {
                                                width: 100
                                                height: parent.height
                                                IconButton {
                                                    anchors.centerIn: parent
                                                    displayText:"\uf067"
                                                    onIconBtnClicked:{
                                                        masterController.ui_commander.setUpStockItems([],"update stock")
                                                        masterController.ui_commander.setUpdateStockId(modelData._id);
                                                    }
                                                }
                                                Text {
                                                     anchors.right: parent.right
                                                     width: parent.width/2
                                                     height: parent.height
                                                     font.pixelSize: 15
                                                     text:"Add"
                                                     horizontalAlignment: Text.AlignRight
                                                     verticalAlignment: Text.AlignVCenter
                                                }
                                            }*/


                                        }
                                    }
                                }
                            }
                            states: [
                                State {
                                    name: "hover"
                                    PropertyChanges {
                                        target: div
                                        color: "#f0f0f0"
                                        anchors.margins: 3
                                        border{
                                            width: 2
                                        }
                                        parent.height: 50
                                        radius: 5
                                    }
                                    PropertyChanges{
                                        target: actionbar
                                        color: 'green'
                                        visible: true
                                    }
                                }
                            ]
                        }
                    }
                }
            }
        }
    }
}
