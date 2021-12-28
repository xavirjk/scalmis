import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import SCALMIS 1.0
Column {
    property StockItem stockItem
    signal setStates()
    signal refresh();
    Component.onCompleted:function (){
        if(stockItem.ui_state.ui_input) hideModel()
        else openModel();
    }
    function getIndexFromModel(){
        for(let i = 0; i < requests.ui_descComboSelect.ui_combo.length; i++){
            if(requests.ui_descComboSelect.ui_combo[i].ui_key ===
                    stockItem.ui_description.ui_input)return i
        }
        return -1
    }
    function getDt(){
        for(let i = 0; i < requests.ui_itemsComboSelect.ui_combo.length; i++){
            if(requests.ui_itemsComboSelect.ui_combo[i].ui_key ===
                    stockItem.ui_item.ui_input) return i
        }
        return  -1
    }

    function displayModel () {
        return stockItem.ui_quantComboSelect.ui_combo
    }
    function hideModel(){
        model.visible = false
        clbtn.collapsTxt = stockItem.ui_fullItem + '   '+stockItem.ui_totalAmount
    }
    function openModel (){
        if(stockItem.ui_item.ui_input)textDes.visible = true
        model.visible = true;
        clbtn.collapsTxt = ''
    }

    function toggleViews () {
        setStates()
        stockItem.ui_state.ui_input = 0
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
        height: 150
        border.color: Style.defaulttxt_bg
        border.width: 2
        Column {
            anchors.fill: parent
            spacing: 2
            anchors.margins: 5
            Row {
                width: parent.width
                height: parent.height*0.5
                spacing: 2
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
                            model: requests.ui_itemsComboSelect.ui_combo
                            font.pixelSize: 18
                            currentIndex: getDt()
                            displayText: currentIndex === -1? "Please Select Item":currentText
                            font.family: 'Impact, fantacy'
                            onActivated:function(){
                                masterController.ui_commander.cBoxDesc(currentText)
                                combo2Cont.visible = true
                                if(currentText !== stockItem.ui_item.ui_input){
                                    stockItem.ui_item.ui_input = currentText
                                    stockItem.ui_description.ui_input= ""
                                }
                                textDes.visible = false
                            }
                            Component.onCompleted: currentIndex = getDt();
                        }

                    }
                }
                Item {
                    id: textDes
                    visible: false
                    width: parent.width * 1/4
                    height: parent.height *0.7
                    Rectangle {
                        id: main
                        radius: 5
                        anchors{
                            fill: parent
                            centerIn: parent
                            topMargin: 10
                        }
                        StringEditor{
                            anchors.fill: parent
                            textDesc: stockItem.ui_description.ui_input
                        }
                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onEntered:main.state = "hover"
                            onExited: main.state = ""
                            onClicked: {
                                masterController.ui_commander.cBoxDesc(combo1.currentText)
                                textDes.visible = false
                                combo2Cont.visible = true
                            }

                        }
                        states: [
                            State {
                                name: "hover"
                                PropertyChanges {
                                    target: main
                                    color: "green"
                                }
                            }
                        ]
                    }
                }
                Item {
                    id: combo2Cont
                    visible: false
                    width: parent.width*1/3
                    height: parent.height
                    Rectangle {
                        anchors{
                            fill: parent
                            margins: 10
                        }
                        ComboBox {
                            id: combo2
                            width: parent.width * 3/4
                            height: parent.height * 0.8
                            textRole: "ui_key"
                            valueRole: "ui_value"
                            model: requests.ui_descComboSelect.ui_combo
                            font.pixelSize: 18
                            font.family: 'Impact, fantacy'
                            onModelChanged: {
                                currentIndex = getIndexFromModel();
                                displayText = currentIndex === -1? "Description": currentText
                            }
                            onActivated:{
                                stockItem.ui_description.ui_input = currentText
                                combo2.displayText = currentText
                            }
                        }
                    }
                }
                Item {
                    width: 230
                    height: parent.height
                    Rectangle {
                        anchors{
                            fill: parent
                            margins: 10
                        }
                        ComboBox {
                            id: combo
                            width: parent.width * 3/4
                            height: parent.height *0.8
                            textRole: "ui_key"
                            valueRole: "ui_value"
                            model: displayModel()
                            onActivated: function (){
                                stockItem.ui_quantifier.ui_input = combo.currentValue
                                if(stockItem.ui_quantifier.ui_input){
                                    stockItem.ui_amountAdded.ui_label = "Number of "+combo.currentText+"s"
                                }
                                else {
                                    stockItem.ui_amountAdded.ui_label = "Number"
                                }
                            }
                            Component.onCompleted: currentIndex = indexOfValue(stockItem.ui_quantifier.ui_input)
                        }

                    }
                }
            }
            Row {
                width: parent.width
                height: parent.height*0.4
                spacing: 10
                Item {
                    width: comboCont.width
                    height: parent.height
                    Rectangle {
                        anchors.leftMargin: 10;anchors.fill: parent
                        IntInput {
                            intDecorator: stockItem.ui_amountAdded
                            cardHeight: parent.height
                            width: 250
                        }
                    }
                }


                Rectangle {
                    color: "#f0f0f0";
                    width: 250
                    height: parent.height;
                    Column {
                        spacing: 2
                        width: parent.width
                        Rectangle {
                            height: 19
                            width: parent.width
                            color: "#f0f0f0"
                                StringEditor {
                                    anchors.fill: parent
                                    setH: true
                                    textDesc: "Computed Tally"
                                }
                        }
                        Rectangle {
                            height: 19
                            color: "#f0f0f0"
                            width: parent.width
                            StringEditor {
                                anchors.fill: parent
                                setH:false
                                textDesc: stockItem.ui_totalAmount
                            }
                        }
                        Rectangle {
                            id: availabilityCard
                            height: 19
                            visible: false
                            color: "#f0f0f0"
                            radius: 5
                            border.color: 'red'
                            border.width: 2
                            width: parent.width
                            StringEditor {
                                id: avCEditor
                                anchors.fill: parent
                                setH:true
                                textDesc: ''
                            }
                        }
                    }
                }
            }
        }
    }
}
