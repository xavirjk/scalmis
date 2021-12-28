import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import components 1.0
import SCALMIS 1.0
Item {
    property InvoicePeriod period: masterController.ui_invoicePeriod
    Rectangle {
        id: rI
        anchors {
            top: parent.top
            bottom: parent.bottom
        }
        width: contentFrame.width
        anchors.margins: 10
        Column {
            spacing: 2
            width: parent.width-100
            Rectangle {
                width: parent.width;
                height: 35
                color: "#f0f0f0"
                StringEditor {
                    anchors.verticalCenter: parent.verticalCenter
                    textDesc: "Date Format: YYYY-MM-DD"
                }
            }
            Rectangle {
                width: parent.width
                height: 120
                radius: 3
                border.color: Style.defaulttxt_bg
                border.width: 2
                Row {
                    height: parent.height
                    width: parent.width*0.7
                    spacing: 2
                    anchors.margins: 3
                    DateInput {
                        dateTimeDecorator: period.ui_from
                        cardHeight:  60
                        width: parent.width/2
                    }
                    DateInput {
                        dateTimeDecorator: period.ui_to
                        cardHeight:  60
                        width: parent.width/2
                    }
                }
            }
            CommandBar {
                commandList: masterController.ui_commander.ui_contextCommands
            }
        }
    }
}
