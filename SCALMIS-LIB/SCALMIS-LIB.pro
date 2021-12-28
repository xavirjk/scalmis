QT += core network qml gui

TEMPLATE = lib
DEFINES += SCALMISLIB_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += source
SOURCES += \
    source/controllers/commandcontroller.cpp \
    source/controllers/mastercontroller.cpp \
    source/data/comboselect.cpp\
    source/data/comboselectdata.cpp\
    source/data/datadecorator.cpp \
    source/data/datetimedecorator.cpp \
    source/data/entity.cpp \
    source/data/intdecorator.cpp \
    source/data/stringdecorator.cpp \
    source/flow/commands.cpp \
    source/models/accounts.cpp \
    source/models/authlogin.cpp \
    source/models/invoiceperiod.cpp \
    source/models/itemdescriptives.cpp \
    source/models/requestitem.cpp \
    source/models/requests.cpp \
    source/models/scalmislib.cpp \
    source/models/service.cpp \
    source/models/stock.cpp \
    source/models/stockitem.cpp \
    source/network/networkaccessmanager.cpp \
    source/network/serverrequest.cpp \
    source/validators/validators.cpp

HEADERS += \
    source/SCALMIS-LIB_global.h \
    source/controllers/commandcontroller.h \
    source/controllers/mastercontroller.h \
    source/controllers/navigationcontroller.h \
    source/data/comboselect.h\
    source/data/comboselectdata.h\
    source/data/datadecorator.h \
    source/data/datetimedecorator.h \
    source/data/entity.h \
    source/data/entitycollection.h \
    source/data/intdecorator.h \
    source/data/stringdecorator.h \
    source/flow/commands.h \
    source/models/accounts.h \
    source/models/authlogin.h \
    source/models/invoiceperiod.h \
    source/models/itemdescriptives.h \
    source/models/requestitem.h \
    source/models/requests.h \
    source/models/scalmislib.h \
    source/models/service.h \
    source/models/stock.h \
    source/models/stockitem.h \
    source/network/inetworkaccessmanager.h \
    source/network/iserverrequest.h \
    source/network/networkaccessmanager.h \
    source/network/serverrequest.h \
    source/validators/validators.h

# Default rules for deployment.

unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
