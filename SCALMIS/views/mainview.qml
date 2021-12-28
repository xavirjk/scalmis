import QtQuick 2.9
import QtQuick.Window 2.12
import QtQuick.Controls 2.2
import assets 1.0
import SCALMIS 1.0
import components 1.0

Window {
    visible: true
    width: Style.widthWindow
    height: Style.heightWindow
    title: masterController.ui_title
    function setPopup(message){
        succText.visible = true;
        textDisplay.text = message;
        timer.delay(function(){succText.visible = false}, 2500)
    }
    Connections {
        target: masterController.ui_commander
        function onServerResponse(message){
            masterController.ui_commander.resetCommands();
            setPopup(message);
        }
    }
    Connections {
        target: masterController.ui_navigator
        function onGoAdminView(){
            menuFrame.replace("qrc:/components/AdminNavBar.qml");
            contentFrame.replace("qrc:/components/Base.qml");
        }
        function onGoLogoutAdmin(){
            menuFrame.replace("qrc:/components/LoginForm.qml")
            contentFrame.replace("qrc:/views/homeview.qml")
        }
    }

    Component.onCompleted: {
        menuFrame.push("qrc:/components/LoginForm.qml");
        contentFrame.push("qrc:/views/homeview.qml");
    }

    StackView {
        id: menuFrame
        property alias dd: shadow
        width: Style.widthWindow/4
        height: parent.height
        Rectangle {
            id: shadow
            x: 30
            y: 40
            width: parent.width - 40
            height: parent.height - 50
            color: Style.defaulttxt_bg
            radius: Style.drpShadowRad
        }
        initialItem: "qrc:/views/splashview.qml"
        clip: true
    }

    StackView {
        id: contentFrame
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: menuFrame.right
        }
        initialItem: "qrc:/views/splashview.qml"
        clip: true
    }
    Timer{
        id:timer
        function delay(callback, span){
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
        id: succText
        visible: false
        height: 40
        color: 'transparent'
        width: contentFrame.width
        anchors {
            top: contentFrame.top
            left: contentFrame.left
            topMargin: 40
        }
        Rectangle {
            width: parent.width - 200
            height: parent.height
            radius: 5
            color: "lightgray"
            anchors.centerIn: parent
            Text {
                id: textDisplay
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: "black"
                text: ""
                font.pixelSize: 18
                font.weight:Font.DemiBold
            }
        }
    }
}
