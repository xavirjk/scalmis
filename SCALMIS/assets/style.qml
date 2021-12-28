pragma Singleton
import QtQuick 2.9
import QtQuick.Window 2.2

Item {
    property alias fontAwesome: fontawesomeLoader.name

    readonly property color color_bg: '#efefef'
    readonly property color defaulttxt_bg: '#2b3b2a'
    readonly property string defaultFontFamily: 'Impact, fantacy'
    readonly property real widthWindow: Screen.width
    readonly property real heightWindow: Screen.height - 70

    readonly property int marginsHomeView: 24
    readonly property int marginSlideView: 10
    readonly property int hOffsetdrpShadow : 8
    readonly property int vOffsetdrpShadow : 10
    readonly property real drpShadowRad : 10.0

    readonly property int navbarElHeight: 60
    readonly property int subNavBarElHeight: 40
    readonly property int navbtnDescHeight: navbarElHeight
    readonly property int navbtnIconHeight: navbarElHeight


    readonly property int pixelSizeSplashView: 40

    readonly property real widthRefWindow: Screen.width - 100
    readonly property real heightRefWindow: Screen.height - 100

    readonly property real heightsearchRes: 150
    readonly property real pixelSizeSearchRes: 14
    readonly property real pixelSizeFirm: 16
    readonly property real heightsearchResEl: 25

    function hscale(size) {
        return Math.round(size *(widthWindow/widthRefWindow));
    }
    function vscale(size) {
        return Math.round(size * (heightWindow/heightRefWindow));
    }
    function tscale(size) {
        return Math.round(hscale(size) + vscale(size)/2);
    }
    FontLoader {
        id: fontawesomeLoader
        source: 'qrc:/assets/fontawesome.otf'
    }
}
