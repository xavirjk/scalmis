import QtQuick 2.9
import assets 1.0
import SCALMIS 1.0
Item {
    property AuthLogin authLogin: masterController.ui_authLogin
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
            height: 200
            spacing: 2

            PageDesc {
                iconChar: "\uf2f5"
                description: "LOGIN"
            }
            IntInput {
                intDecorator: authLogin.ui_pjno
                cardHeight: 80
            }
            StringInput {
                stringDecorator: authLogin.ui_password
                isPassword: true
                cardHeight: 80
            }
            ActionButton {
                id: searchBtn
                onActionBtnClicked: masterController.ui_commander.signin()
                displayText: "SIGN-IN"
            }

        }
    }
}
