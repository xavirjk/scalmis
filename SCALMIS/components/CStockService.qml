import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import SCALMIS 1.0
Column {
    property Service service
    signal setStates()
    signal refresh();
    Component.onCompleted:function (){
        if(service.ui_state.ui_input) hideModel()
        else openModel();
    }
    function hideModel(){
        model.visible = false
        clbtn.collapsTxt = service.ui_service.ui_input
    }
    function openModel (){
        model.visible = true;
        clbtn.collapsTxt = ''
    }

    function toggleViews () {
        setStates()
        service.ui_state.ui_input = 0
        refresh()
    }

    anchors.margins: 10
    spacing: 10
    Rectangle {width:parent.width;height:1.5}
    Collapsable{id: clbtn}
    Column {
        id: model
        width: parent.width
        spacing: 2
        Row {
            width: parent.width
            spacing: 2
            StringInput {
                stringDecorator: service.ui_service
                cardHeight: 60
                width: 700
            }
        }
        Row {
            width: parent.width
            spacing: 2
            StringInput {
                stringDecorator: service.ui_code
                cardHeight: 60
                width: 250
            }
        }
        Rectangle {width: parent.width;height: 20}
    }
}
