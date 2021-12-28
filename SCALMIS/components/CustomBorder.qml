import QtQuick 2.9

Rectangle {
    property bool common_border: true
    property int l_borderW: 1
    property int r_borderW: 1
    property int t_borderW: 1
    property int b_borderW: 1

    property int commonBorderW: 1
    z : -1

    property string borderColor: "white"
    color: borderColor
    anchors {
        fill: parent
        topMargin: common_border ? -commonBorderW : -t_borderW
        bottomMargin: common_border ? -commonBorderW : -b_borderW
        leftMargin: common_border ? -commonBorderW : -l_borderW
        rightMargin: common_border ? -commonBorderW : -r_borderW
    }

}
