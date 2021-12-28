import QtQuick 2.0
Rectangle {
    id: collapsable
    property alias collapsTxt: modelRep.text
    color: "#f0f0f0";
    width: parent.width;
    height: 40;
    Text {
        anchors.fill: parent
        id: modelRep
        text: ''
        font.family: 'consolas'
        font.pixelSize: 20
        font.weight: Font.DemiBold
        color: '#7e7e7e'
        verticalAlignment: Text.AlignVCenter
    }
    MouseArea {
        hoverEnabled: true
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onEntered: collapsable.state = "hover"
        onExited: collapsable.state = ""
        onClicked: toggleViews()
    }
    states: [
        State {
            name: "hover"
            PropertyChanges {
                target: collapsable
                color: 'silver'
            }
        }
    ]
}
