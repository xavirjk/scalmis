import QtQuick 2.9
import assets 1.0
import QtQuick.Controls 2.2
import components 1.0
Item {
    property alias pane: displayPane
    Component.onCompleted: masterController.ui_navigator.goAdminDashboardView()
    signal logout()
    function destroyChildren(){
        for(var i = 0; i< displayPane.children.length; i++){
            displayPane.children[i].destroy()
        }
    }
    function setUpView(pane,data){
        destroyChildren()
        var cmp = Qt.createComponent(pane);
        if(cmp.status === Component.Ready && data)cmp.createObject(displayPane,data)
        else cmp.createObject(displayPane);
    }

    onLogout: masterController.ui_commander.signout_admin()
    Rectangle {
        Connections {
            target: masterController.ui_navigator
            function onGoViewIssuedItems(data){
                setUpView("qrc:/components/ViewIssuedItems.qml",{anArray:data})
            }
            function onGoGetDates(){
                setUpView("qrc:/pages/GenerateInvoice.qml")
            }
            function onGoCheckUpdates(){
                setUpView("qrc:/pages/CheckForUpdates.qml")
            }

            function onGoAdminDashboardView() {
                setUpView("qrc:/components/AdminDashboard.qml")
            }
            function onGoRenderUsers(body){
                setUpView("qrc:/pages/ViewUsers.qml",{anArray: body});
            }

            function onGoCreateNewStockTake(){
                var context = masterController.ui_commander.getContext();
                if(context === 'new service') setUpView("qrc:/pages/NewService.qml");
                else setUpView("qrc:/components/NewStock.qml")
            }
            function onGoRequestItem(){
                setUpView("qrc:/components/RequestItem.qml")
            }
            function onGoViewStock(data){
                setUpView("qrc:/components/ViewStock.qml",{anArray:data})
            }

            function onGoSelectItems(){
                setUpView("qrc:/components/SelectReqItems.qml")
            }
            function onGoSelectServices(){
                setUpView("qrc:/pages/selectReqServices.qml")
            }
            function onGoViewItems(data){
                setUpView("qrc:/components/ViewItems.qml",{anArray:data})
            }
            function onGoCreateNewUser(){
                setUpView("qrc:/components/CreateUser.qml")
            }
            function onGoViewStockItems(type){
                setUpView("qrc:/components/ViewStockItems.qml",{type:type})
            }
        }

        anchors {
            fill: parent
            margins: Style.marginsHomeView
            leftMargin: Style.marginSlideView
        }
        Rectangle {
            id: topBar
            height: 10
            color: Style.defaulttxt_bg
            anchors{
                left: parent.left
                top: parent.top
                right: parent.right
            }
        }
        Rectangle {
            id: topPanel
            height: 65
            width: parent.width
            anchors.top: topBar.bottom
            Rectangle {
                height: parent.height
                width: 200
                Column {
                    spacing: 10
                    anchors.margins: 2

                    Text {
                        font.family: 'Impact ,fantasy'
                        font.pixelSize: 22
                        text: 'Kiambu Law Courts'
                    }
                    Text{
                        font.family: 'Arial Bold'
                        font.pixelSize: 18
                        text: 'Admin'
                    }
                }
            }

            Rectangle {
                id: logoutBtn
                height: parent.height
                width: 60
                anchors{
                    right: parent.right
                }
                PageDesc {
                    iconChar: "\uf2f5"
                }
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onEntered:logoutBtn.state = "hover"
                    onExited: logoutBtn.state = ""
                    onClicked:logout()
                }
                states: [
                    State {
                        name: "hover"
                        PropertyChanges {
                            target: logoutBtn

                        }
                    }
                ]
            }
        }

        Rectangle {
            width: parent.width
            color: "beige"
            anchors {
                margins: 10
                top: topPanel.bottom
                bottom: parent.bottom
            }
            Rectangle {
                anchors.fill: parent
                id: displayPane
                }
            }
        }
}
