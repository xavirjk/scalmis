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
    function getDt(){
        for(let i = 0; i < requests.ui_srvComboSelect.ui_combo.length; i++){
            if(requests.ui_srvComboSelect.ui_combo[i].ui_key ===
                    service.ui_service.ui_input) return i
        }
        return  -1
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
    Collapsable {id: clbtn}
    Rectangle {
        id:model
        width: parent.width
        radius: 3
        height: 60
        border.color: Style.defaulttxt_bg
        border.width: 2
        Item {
            id: comboCont
            width: parent.width*0.4
            height: parent.height
            Rectangle {
                anchors{
                    fill: parent
                    margins: 10
                }
                ComboBox {
                    id: combo1
                    width: parent.width * 3/4
                    height: parent.height *0.8
                    textRole: "ui_key"
                    valueRole: "ui_value"
                    model: requests.ui_srvComboSelect.ui_combo;
                    font.pixelSize: 18
                    currentIndex: getDt()
                    displayText: currentIndex === -1? "Please Select A Service":currentText
                    font.family: 'Impact, fantacy'
                    onActivated:function(){
                        if(currentText !== service.ui_service.ui_input)
                            service.ui_service.ui_input = currentText
                    }
                    Component.onCompleted: currentIndex = getDt();
                }
            }
        }
    }
}
