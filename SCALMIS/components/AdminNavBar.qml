import QtQuick 2.9
import assets 1.0
Item {
    Rectangle {
        id: homepane
        radius: Style.drpShadowRad
        anchors {
            fill: parent
            margins: Style.marginsHomeView
        }

        Rectangle {
            id: tst
            height: 5
            color: Style.defaulttxt_bg
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }
        }
        Column {
            width: parent.width
            spacing: 2
            NavigationButton {setH: 10;iconChar: '';description: ''}
            Rectangle {
                width: parent.width;height: 100
                Image {
                    id: img
                    source: "qrc:/assets/judiciaryLogo.jpg"
                    anchors.centerIn: parent
                    sourceSize: Qt.size(200, parent.height)
                }
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: masterController.ui_navigator.goAdminDashboardView()
                }
            }
            NavigationButton {
                iconChar: '\uf015'
                description: 'Home Page'
                setH: Style.navbarElHeight
                onNavBtnClicked: masterController.ui_navigator.goAdminDashboardView()
            }
            NavigationButton {
                iconChar: '\uf15c'
                description: 'New Stock-Take'
                setH: Style.navbarElHeight
                onNavBtnClicked:{
                    itemBar.visible = !itemBar.visible
                }
            }
            Item {
                width: parent.width
                id: itemBar
                height: 100
                visible: false
                Column {
                    spacing: 2
                    anchors .right: parent.right
                    width: parent.width*0.8
                    NavigationButton {
                            iconChar: '\uf5fd'
                            description: 'Item'
                            setH: Style.subNavBarElHeight
                            onNavBtnClicked: masterController.ui_commander.setUpStockItems([],'new stock');
                    }
                    NavigationButton {
                        iconChar: '\uf073'
                        description: "Service"
                        setH: Style.subNavBarElHeight
                        onNavBtnClicked: masterController.ui_commander.setUpStockItems([], 'new service');
                    }
                }
            }
            NavigationButton {
                iconChar: '\uf044'
                description: 'Edit-Stock'
                setH: Style.navbarElHeight
                onNavBtnClicked: masterController.ui_commander.getStockTakes()
            }
            NavigationButton {
                iconChar: '\uf79c'
                description: 'Request Item'
                setH: Style.navbarElHeight
                onNavBtnClicked:{
                     masterController.setContext(1)
                     masterController.ui_commander.cBoxItems()
                }
            }
            NavigationButton {
                iconChar: '\uf1d8'
                description: 'Issue Item'
                setH: Style.navbarElHeight
                onNavBtnClicked: masterController.ui_commander.getApproved(false,"false")
            }
            NavigationButton {
                iconChar: '\uf381'
                description: 'Downloads'
                setH: Style.navbarElHeight
                onNavBtnClicked:  {
                    masterController.setContext(2)
                    masterController.ui_commander.cBoxAuths()
                }
            }
            NavigationButton {
                iconChar: '\uf085'
                description: 'Updates'
                setH: Style.navbarElHeight
                onNavBtnClicked: masterController.ui_commander.checkUpdates("scalmis","project");
            }

        }
    }
}
