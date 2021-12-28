QT += quick core5compat

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += source \
    ../SCALMIS-LIB/source

SOURCES += \
        source/main.cpp

RESOURCES += views.qrc \
    assets.qrc \
    components.qrc \
    pages.qrc

RC_ICONS = icon.ico
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD

LIBS += -L$$PWD/../shadow-builds/SCALMIS-LIB/debug -lSCALMIS-LIB
LIBS += -L$$PWD/../shadow-builds/ssl -llibcrypto-3-x64
LIBS += -L$$PWD/../shadow-builds/ssl -llibssl-3-x64
# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
