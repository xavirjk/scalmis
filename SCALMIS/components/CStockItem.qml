import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import SCALMIS 1.0
import "../assets/index.js" as Index
Column {
    property StockItem stockItem
    signal setStates()
    signal refresh();
    Component.onCompleted:function (){
        if(stockItem.ui_quantifier.ui_input) {
            stockItem.ui_amountAdded.ui_label = "Number of "+Index.indexOfEq(displayModel(),stockItem.ui_quantifier.ui_input)+"s"
            stockItem.ui_assetValue.ui_label = "Cost per "+Index.indexOfEq(displayModel(), stockItem.ui_quantifier.ui_input);
        }
        if(stockItem.ui_state.ui_input) hideModel()
        else openModel();
        if(masterController.ui_commander.getContext() === 'item update'){
            row1.visible  = false;itCode.visible = false;assetVal.visible = false;
            stockItem.ui_amountAdded.ui_input = 0
        }
    }
    function displayModel () {
        return stockItem.ui_quantComboSelect.ui_combo
    }
    function hideModel(){
        model.visible = false
        clbtn.collapsTxt = stockItem.ui_fullItem+"  " +stockItem.ui_totalAmount +"  "+ stockItem.ui_totalCost
    }
    function openModel (){
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
    Collapsable{id: clbtn}
    Column {
        id: model;width: parent.width;spacing: 2
        Row {
            id:row1;width: parent.width;spacing: 2
            StringInput {stringDecorator: stockItem.ui_item;cardHeight: 60;width: 250}
            StringInput {stringDecorator: stockItem.ui_description;cardHeight: 60;width: 250}
            Item {
                width: 200;height: 80
                Rectangle {
                    anchors{fill: parent;margins: 10}
                    ComboBox {
                        id: combo
                        width: parent.width * 3/4
                        height: parent.height / 2
                        textRole: "ui_key"
                        valueRole: "ui_value"
                        model: displayModel()
                        onActivated: function (){
                            stockItem.ui_quantifier.ui_input = combo.currentValue
                            stockItem.ui_pricing.ui_input = 0
                            combo2.currentIndex = 1
                            if(stockItem.ui_quantifier.ui_input){
                                stockItem.ui_amountAdded.ui_label = "Number of "+combo.currentText+"s"
                                stockItem.ui_assetValue.ui_label = "cost per " +combo.currentText
                            }
                            else {
                                stockItem.ui_amountAdded.ui_label = "Number"
                                stockItem.ui_assetValue.ui_label = "Value"
                            }
                            if(!combo.currentValue) combo2cont.visible = false
                            else combo2cont.visible = true
                        }
                        Component.onCompleted: currentIndex = indexOfValue(stockItem.ui_quantifier.ui_input)
                    }

                }
            }
            Component.onCompleted: function(){
                if(stockItem.ui_quantifier.ui_input)combo2cont.visible = true
                else combo2cont.visible = false
            }

            Item {
                visible: false;id: combo2cont;width: 250;height: 80
                Rectangle {
                    anchors{fill: parent;margins: 10}
                    ComboBox {
                        id: combo2
                        width: parent.width * 3/4
                        height: parent.height / 2
                        textRole: "ui_key"
                        valueRole: "ui_value"
                        model: stockItem.ui_pricingComboSelect.ui_combo
                        onActivated: function(){
                            stockItem.ui_pricing.ui_input = combo2.currentValue
                            if(stockItem.ui_pricing.ui_input === 1){
                                stockItem.ui_amountAdded.ui_label = "Number"
                                stockItem.ui_assetValue.ui_label = "Total Cost"
                            }
                            else {
                                stockItem.ui_amountAdded.ui_label = "Number of "+combo.currentText+"s"
                                stockItem.ui_assetValue.ui_label = "cost per " +combo.currentText
                            }
                        }
                        Component.onCompleted: currentIndex = indexOfValue(stockItem.ui_pricing.ui_input)
                    }

                }
            }
        }
        Row {
            width: parent.width;spacing: 2
            IntInput {id:assetVal;intDecorator: stockItem.ui_assetValue;cardHeight: 60;width: 250}
            IntInput {intDecorator: stockItem.ui_amountAdded;cardHeight: 60;width: 250}
            StringInput {id:itCode;stringDecorator: stockItem.ui_code;cardHeight: 60;width: 250}
        }
        Rectangle {width: parent.width;height: 20}
        Row {
            width: parent.width
            spacing: 2
            Rectangle {
                color: "#f0f0f0";
                width: 300
                height: 70;
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
                            setH: false
                            textDesc: stockItem.ui_totalAmount
                        }
                    }
                    Rectangle {
                        height: 19
                        color: "#f0f0f0"
                        width: parent.width
                        StringEditor {
                            anchors.fill: parent
                            setH: false
                            textDesc: stockItem.ui_totalCost
                        }
                    }
                }
            }
        }
    }
}
