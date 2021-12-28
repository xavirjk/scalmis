import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import components 1.0
import SCALMIS 1.0
import "../assets/index.js" as Index
Item {
    Component.onCompleted: function(){
        timer.delay(function(){
            masterController.ui_commander.useApprContext()
        },10000)
    }
    property var anArray: []
    function getLocalDateString(timeString){
        const date = new Date(timeString);
        return date.toLocaleString(Locale.ShortFormat)
    }
    function getWidth(){
        return dd.width - 24.5
    }
    Timer{
        id:timer
        function delay(callback,span){
            timer.interval = span;
            timer.repeat = false;
            timer.triggered.connect(callback)
            timer.triggered.connect(function release(){
                timer.triggered.disconnect(callback);
                timer.triggered.disconnect(release);
            });
            timer.start();
        }
    }
    Rectangle {
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
                textDesc: "Items Log:"
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
                id: officeBox
                width: parent.width*0.16
                height: parent.height
                color: "green"
                StringEditor {
                    anchors.fill: parent
                    textDesc: "Office"
                    setH: true
                }

            }
            Rectangle {
                id:idBox
                width: parent.width*0.15
                height: parent.height
                color: "green"
                StringEditor {
                    anchors.fill: parent
                    textDesc: "Officer Identity"
                    setH: true
                }

            }
            Rectangle {
                id:itemBox
                width: parent.width*0.22
                height: parent.height
                color: "green"
                StringEditor {
                    anchors.fill: parent
                    textDesc: "Item Description"
                    setH: true
                }

            }
            Rectangle {
                id: quantRef
                width: parent.width*0.06
                height: parent.height
                color: "green"
                StringEditor {
                    anchors.fill: parent
                    textDesc: "QTY/"
                    setH: true
                }

            }
            Rectangle {
                id: dateBox
                width: parent.width*0.13
                height: parent.height
                color: "green"
                StringEditor {
                    anchors.fill: parent
                    textDesc: "Date Posted"
                    setH: true
                }

            }
            Rectangle {
                id:actionBox
                width: parent.width*0.17
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
            height: 450
            clip: true
            Column {
                spacing: 4
                width: parent.width
                id:col
                Repeater {
                    model: anArray
                    Rectangle {
                        width: dd.width-24.5
                        height: 50
                            Rectangle {
                                id: div
                                width: parent.width - 20
                                height: parent.height
                                anchors.right: parent.right
                                anchors.margins: 5
                                color: "#f0f0f0"
                                radius: 2
                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered:div.state = "hover"
                                    onExited: div.state = ""
                                    Row{
                                        anchors.centerIn: parent
                                        anchors.leftMargin: 1
                                        width: parent.width - 2
                                        spacing: 10
                                        height: parent.height-10
                                        Rectangle {
                                            width: officeBox.width
                                            height: parent.height
                                            color: 'transparent'
                                            Text {
                                                anchors.fill: parent
                                                font.pixelSize: 15
                                                text: ''
                                                verticalAlignment: Text.AlignVCenter
                                                horizontalAlignment: Text.AlignLeft
                                                anchors.leftMargin: 10
                                                Component.onCompleted: text = Index.truncateOffice(modelData)
                                            }
                                        }
                                        Rectangle {
                                            width: idBox.width
                                            height: parent.height
                                            color: 'transparent'
                                            Text {
                                                anchors.fill: parent
                                                font.pixelSize: 14
                                                text: ''
                                                verticalAlignment: Text.AlignVCenter
                                                horizontalAlignment: Text.AlignLeft
                                                anchors.leftMargin: 10
                                                Component.onCompleted: text = Index.truncateName(modelData)
                                            }
                                        }
                                        Rectangle {
                                            width: itemBox.width
                                            height: parent.height
                                            color: 'transparent'
                                            Text {
                                                anchors.fill: parent
                                                font.pixelSize: 14
                                                text:''
                                                verticalAlignment: Text.AlignVCenter
                                                horizontalAlignment: Text.AlignLeft
                                                anchors.leftMargin: 10
                                                Component.onCompleted: text =Index.truncated(modelData)
                                            }
                                        }
                                        Rectangle {
                                            width: quantRef.width
                                            height: parent.height
                                            color: 'transparent'
                                            Text {
                                                anchors.fill: parent
                                                font.pixelSize: 14
                                                text: modelData.quantity? modelData.quantity: 1
                                                verticalAlignment: Text.AlignVCenter
                                                horizontalAlignment: Text.AlignLeft
                                                anchors.leftMargin: 10
                                            }
                                        }
                                        Rectangle {
                                            width: dateBox.width
                                            height: parent.height
                                            color: 'transparent'
                                            Text {
                                                anchors.fill: parent
                                                font.pixelSize: 14
                                                text: getLocalDateString(modelData.issuedAt)
                                                verticalAlignment: Text.AlignVCenter
                                                horizontalAlignment: Text.AlignLeft
                                                anchors.leftMargin: 10
                                            }
                                        }
                                        Rectangle {
                                            id:actionbar
                                            color: 'transparent'
                                            visible: false
                                            width: actionBox.width
                                            height: parent.height
                                            Row {
                                                anchors{
                                                    fill: parent
                                                    topMargin: 4
                                                }
                                                spacing: 3
                                                Text {
                                                    id: approval
                                                    width: parent.width * 0.7
                                                    height: parent.height
                                                    text: modelData.approved? "Reject": "Approve"
                                                    verticalAlignment: Text.AlignVCenter
                                                    horizontalAlignment: Text.AlignHCenter
                                                    font.family: "consolas"
                                                    font.pixelSize: 20
                                                    font.weight: Font.DemiBold
                                                    color: modelData.approved? "red": "green"
                                                    MouseArea {
                                                        anchors.fill: parent
                                                        hoverEnabled: true
                                                        cursorShape: Qt.PointingHandCursor
                                                        onClicked: masterController.ui_commander.doApproval(modelData.approved,modelData._id)
                                                    }

                                                }
                                                IconButton {
                                                    displayText: '\uf381'
                                                    onIconBtnClicked:
                                                        masterController.ui_commander.generateInvoice(modelData)
                                                }

                                            }
                                        }
                                    }
                                }
                                states: [
                                    State {
                                        name: "hover"
                                        PropertyChanges {
                                            target: div
                                            color: 'silver'
                                            anchors.margins: 3
                                            parent.height: 55
                                            radius: 4

                                        }
                                        PropertyChanges{
                                            target: actionbar
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
