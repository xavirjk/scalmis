import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import components 1.0
import SCALMIS 1.0
Item {
    property Requests requests: masterController.ui_requests
    Component.onCompleted: {
        masterController.setContext(0)
        masterController.ui_commander.cBoxItems();
    }
    function getBelowMark(mark){
        let depleted = 0
        let combo = requests.ui_itemsComboSelect.ui_combo.length;
        for(let i = 0 ; i < combo; i++){
            if(requests.ui_itemsComboSelect.ui_combo[i].ui_value <= mark)depleted+=1
        }
        return depleted;
    }
    function cRBIWidth(){
        return cRBI.width/3 - 5
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
            id:dd
            width: parent.width -100;
            height: 35
            color: "green"
            StringEditor {
                anchors.fill: parent
                setH: true
                anchors.verticalCenter: parent.verticalCenter
                textDesc: "Procurement Supply Chain and Logistics Management Information System"
            }
        }
        Rectangle {
            id: topMenu
            anchors.top: dd.bottom
            width: parent.width - 100
            height: 150
            Rectangle {
                radius: 3
                border {
                    color: '#e98f19'
                    width: 2
                }

                anchors {
                    left: parent.left
                    top: parent.top
                    margins: 10
                }
                id: createUser
                width: parent.width *0.32
                height: 120
                NavigationButton {
                    setH: parent.height
                    iconChar: '\uf234'
                    description: "New"
                    setP: 70
                    setTP: 30
                    setICW: parent.width *0.4
                    setTPW: parent.width * 0.6
                    onNavBtnClicked: {
                        masterController.ui_commander.setContextCommands("create-profile")
                        masterController.ui_navigator.goCreateNewUser()
                    }
                }
            }
            Rectangle {
                radius: 3
                border {
                    color: '#e98f19'
                    width: 2
                }
                anchors{
                    left: createUser.right
                    top: parent.top
                    margins: 10
                }
                id: editUser
                width: createUser.width
                height: createUser.height
                NavigationButton {
                    setH: parent.height
                    iconChar: '\uf4ff'
                    description: "Edit"
                    setP: 70
                    setTP: 30
                    setICW: parent.width *0.4
                    setTPW: parent.width * 0.6
                    onNavBtnClicked:{
                        masterController.setContext(3);
                        masterController.ui_commander.cBoxAuths();
                    }
                }
            }
            Rectangle {
                radius: 3
                border {
                    color: '#e98f19'
                    width: 2
                }
                anchors{
                    left: editUser.right
                    top: parent.top
                    margins: 10
                }
                id: totalIssued
                width: createUser.width
                height: createUser.height
                NavigationButton {
                    setH: parent.height
                    iconChar: '\uf79c'
                    description: 'All Reqests'
                    setP: 70
                    setTP: 30
                    setICW: parent.width*0.4
                    setTPW: parent.width*0.6
                    onNavBtnClicked: masterController.ui_commander.getApproved(false,"")
                }
            }
            Rectangle {
                //color: 'red' center
                anchors {
                    top: topMenu.bottom
                    left: parent.left
                    right: parent.right
                }
                height: 350
                Rectangle {
                    id:homeLeftMenu
                    width: parent.width/2 - 20
                    height: parent.height
                    //color: "green" left
                    Column {
                        anchors.top: parent.top
                        spacing: 2
                        width: parent.width
                        Rectangle{width: parent.width;height: 10;color: '#e98f19'}
                        Rectangle {
                            width: parent.width
                            height: 30
                            Rectangle {
                                width: parent.width*0.55;height: parent.height
                                Text {
                                    anchors.right: parent.right
                                    text: 'Stock'
                                    font.pixelSize: 16
                                    color: '#e98f19'
                                    verticalAlignment: Text.AlignVCenter
                                    horizontalAlignment: Text.AlignHCenter

                                }
                            }
                            Rectangle {
                                width: 30;height: parent.height
                                anchors.right: parent.right
                                NavigationButton {
                                    setH:parent.height ;iconChar: '\uf381'
                                    setICW:20;setTPW:0;setP:20
                                    hideHoverbcg:true;noMargins:true
                                    onNavBtnClicked: masterController.ui_commander.downloadStock()
                                }
                            }


                        }
                        Row {
                            id:stockRow
                            width: parent.width
                            height: 90
                            spacing: 2
                            Rectangle {
                                id:stockBox
                                width: parent.width * 0.33
                                height: parent.height
                                Column {
                                    width: parent.width
                                    NavigationButton {
                                        id:item
                                        setH:stockBox.height * 0.6 ;description: requests.ui_itemsComboSelect.ui_combo.length;
                                        setICW:0;setTPW:parent.width;setTP: 50;
                                        topCenterAlign:true;hideHoverbcg:true;noMargins:true
                                        onNavBtnClicked: masterController.ui_navigator.goViewStockItems('all')

                                    }
                                    NavigationButton {
                                        setH:20 ;description: 'Items';setICW:0;setTPW:parent.width
                                        topCenterAlign:true;hideHoverbcg:true;noMargins:true
                                    }
                                }
                            }
                            Rectangle {
                                width: parent.width * 0.33
                                height: parent.height
                                Column {
                                    width: parent.width
                                    NavigationButton {
                                        id:onDepletion
                                        setH:stockBox.height * 0.6 ;description: getBelowMark(10);
                                        setICW:0;setTPW:parent.width;setTP: 50;
                                        topCenterAlign:true;hideHoverbcg:true;noMargins:true
                                        onNavBtnClicked: masterController.ui_navigator.goViewStockItems('onDepletion')

                                    }
                                    NavigationButton {
                                        setH:20 ;description: 'Depletion Bound';setICW:0;setTPW:parent.width
                                        topCenterAlign:true;hideHoverbcg:true;noMargins:true
                                    }
                                }
                            }
                            Rectangle {
                                width: parent.width * 0.33
                                height: parent.height
                                Column {
                                    width: parent.width
                                    NavigationButton {
                                        id:depleted
                                        setH:stockBox.height * 0.6 ;description: getBelowMark(0);
                                        setICW:0;setTPW:parent.width;setTP: 50;
                                        topCenterAlign:true;hideHoverbcg:true;noMargins:true
                                        onNavBtnClicked: masterController.ui_navigator.goViewStockItems('depleted')
                                    }
                                    NavigationButton {
                                        setH:20 ;description: 'Depleted';setICW:0;setTPW:parent.width
                                        topCenterAlign:true;hideHoverbcg:true;noMargins:true
                                    }
                                }
                            }
                        }
                        Rectangle {
                            width: parent.width
                            height:200;radius: 1
                            border{width: 2;color: '#f0f0f0'}
                            Text {
                                height: 30
                                width: parent.width/4
                                text:" Overview"
                                font.pixelSize: 18
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.family: "Arial Bold"
                                font.weight: Font.Bold
                            }
                        }
                    }
                }
                Rectangle {
                    anchors.right: parent.right
                    width: parent.width/2 - 20
                    height: parent.height
                    Column {
                        anchors.top: parent.top
                        spacing: 2
                        width: parent.width
                        Rectangle{width: parent.width;height: 10;color: '#e98f19'}
                        Rectangle {
                            width: parent.width
                            height: 30
                            Text {
                                anchors.fill: parent
                                text: new Date().toLocaleDateString(Locale.ShortFormat)
                                font.underline: true
                                font.pixelSize: 16
                                color: '#e98f19'
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter

                            }
                        }
                        Row {
                            width: parent.width
                            spacing: 2
                            Column {
                                id:todayactCol
                                width: parent.width/3
                                spacing: 10
                                Rectangle {
                                    width: parent.width
                                    height: 60
                                    NavigationButton {
                                        setH: parent.height
                                        iconChar: '\uf291'
                                        description: 'Approve Items'
                                        setP: 20
                                        hideHoverbcg: true
                                        onNavBtnClicked: masterController.ui_commander.getApproved(true,'false')
                                    }
                                }
                                Rectangle {
                                    width: parent.width
                                    height: 60
                                    NavigationButton {
                                        setH: parent.height
                                        iconChar: '\uf560'
                                        description: 'view Issued'
                                        setP: 20
                                        hideHoverbcg: true
                                        onNavBtnClicked: masterController.ui_commander.getApproved(true,"true")
                                    }
                                }
                                Rectangle {
                                    width: parent.width
                                    height: 60
                                    NavigationButton {
                                        setH: parent.height
                                        iconChar: '\uf071'
                                        description: 'failed requests'
                                        setP: 20
                                        hideHoverbcg: true
                                        //onNavBtnClicked: masterController.ui_commander.getApproved("")
                                    }
                                }
                                Rectangle {
                                    width: parent.width
                                    height: 60
                                    NavigationButton {
                                        setH: parent.height
                                        iconChar: '\uf79c'
                                        description: 'view Issued'
                                        setP: 20
                                        hideHoverbcg: true
                                        //onNavBtnClicked: masterController.ui_commander.getApproved("")
                                    }
                                }
                            }
                            Rectangle {
                                width: parent.width - todayactCol.width
                                height: todayactCol.height
                                color: '#f0f0f0'
                                Column {
                                    anchors.fill: parent
                                    spacing: 2
                                    Rectangle {
                                        width: parent.width
                                        height: 60

                                    }
                                    Rectangle {
                                        width: parent.width
                                        height: 40
                                        Rectangle {
                                            width: parent.width*0.6
                                            height: parent.height
                                            anchors.centerIn: parent
                                            NavigationButton {
                                                setH: parent.height
                                                iconChar: '\uf0ae'
                                                description: 'Request Timeline'
                                                setP: 20
                                                hideHoverbcg: true
                                            }
                                        }
                                    }
                                    Row {
                                        width: parent.width
                                        spacing: 2
                                        height: 40
                                        Rectangle {
                                            width:parent.width*0.28;height: parent.height
                                            Text {
                                                anchors.fill: parent
                                                verticalAlignment: Text.AlignVCenter
                                                horizontalAlignment: Text.AlignHCenter
                                                text: 'Highcourt\nReg 10'
                                            }
                                        }
                                        Rectangle {
                                            width:parent.width*0.28;height: parent.height
                                            Text {
                                                anchors.fill: parent
                                                verticalAlignment: Text.AlignVCenter
                                                horizontalAlignment: Text.AlignHCenter
                                                text: 'Civil Reg\n6'
                                            }
                                        }
                                        Rectangle {
                                            width:parent.width*0.28;height: parent.height
                                            Text {
                                                anchors.fill: parent
                                                verticalAlignment: Text.AlignVCenter
                                                horizontalAlignment: Text.AlignHCenter
                                                text: 'Criminal\nReg 4'
                                            }
                                        }
                                        Rectangle {
                                            width:parent.width*0.14 - 1;height: parent.height
                                            Text {
                                                anchors.fill: parent
                                                verticalAlignment: Text.AlignVCenter
                                                horizontalAlignment: Text.AlignHCenter
                                                text: '+22 \nOthers'
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        Row {
                            id:cRBI
                            width: parent.width
                            height: 30
                            spacing: 8
                            Rectangle {
                                width: cRBIWidth();height: parent.height; color: 'grey'
                                radius: 4
                                StringEditor {
                                    anchors.fill: parent
                                    textDesc: 'pending:12'
                                    setH: true
                                }
                            }
                            Rectangle {
                                width: cRBIWidth();height: parent.height;color: 'red'
                                radius: 4
                                StringEditor {
                                    anchors.fill: parent
                                    textDesc: 'nullified:6'
                                    setH: true
                                }
                            }
                            Rectangle {
                                width: cRBIWidth();height: parent.height;color: 'green'
                                radius: 4
                                StringEditor {
                                    anchors.fill: parent
                                    textDesc: 'approved:18'
                                    setH: true
                                }
                            }  
                        }
                    }
                }
            }
        }
    }
}
