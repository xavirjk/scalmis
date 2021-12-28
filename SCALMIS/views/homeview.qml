import QtQuick 2.9
import assets 1.0
import QtQuick.Controls 2.2
Item {
    Component.onCompleted:initiated(0)
    function initiated(index){
        const imgs = ["fresha.jpg","dormans2C.jpg","javac.jpg","electricals.jpg","boxFiles.jpg","keringet.jpg","towels.jpg"];
        if(index === imgs.length) index = 0
        timer.delay(function(){img.source = 'qrc:/assets/'+imgs[index]},index,10000)
  }
    Timer{
        id:timer
        function delay(callback,index,span){
            timer.interval = span;
            timer.repeat = false;
            timer.triggered.connect(callback)
            timer.triggered.connect(function release(){
                timer.triggered.disconnect(callback);
                timer.triggered.disconnect(release);
                initiated(++index)
            });
            timer.start();
        }
    }
    Rectangle {
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
            width: parent.width
            color: "transparent"
            anchors {
                margins: 10
                top: topBar.bottom
                bottom: parent.bottom
            }
            Image {
                anchors.margins: 40
                id: img
                source: "qrc:/assets/towels.jpg"
                anchors.centerIn: parent
                sourceSize: Qt.size(parent.width, parent.height)
                anchors.fill: parent
            }
            Rectangle {
                id: inforView
                width: 400
                height: 200
                color: "transparent"
                anchors {
                    left: parent.left
                    top: parent.top
                    margins: 20
                }
                Text {
                    id: description
                    width: parent.width
                    height: parent.height / 2
                    text: "SCALMIS"
                    font.pixelSize: 22
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: "Impact, fantacy"
                    color: Style.defaulttxt_bg
                }
                Text {
                    width: parent.width
                    anchors {
                        top:description.bottom
                        bottom: parent.bottom
                    }
                    text: 'Initializing...'
                    font.pixelSize: 50
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop
                    font.family: "Impact, fantacy"
                }
            }
            Rectangle {
                id:footer
                anchors {
                    bottom: parent.bottom
                    left: parent.left
                    right: parent.right
                }
                Text {
                    anchors.fill: parent
                    text: "%1 %2".arg("\uf1f9").arg(new Date().getFullYear())
                    font.pixelSize: 18
                    font.family: Style.fontAwesome
                    color: Style.defaulttxt_bg
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                }

                height: 30
            }
        }
    }
}
