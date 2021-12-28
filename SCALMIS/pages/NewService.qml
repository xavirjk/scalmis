import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import components 1.0
import SCALMIS 1.0
Item {
    property Stock newStock: masterController.ui_stock
    Rectangle {
        id: nS
        anchors {
            top: parent.top
            bottom: parent.bottom
        }
        width: contentFrame.width
        anchors.margins: 10
        ServiceEditor {
            stock: newStock
            width: nS.width
        }
    }
}
