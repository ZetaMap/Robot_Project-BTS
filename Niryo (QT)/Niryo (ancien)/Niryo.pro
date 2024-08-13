QT -= gui
QT += network serialbus

TEMPLATE = lib
DEFINES += NIRYO_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    niryoinfo.cpp \
    poseniryo.cpp \
    niryocontroller.cpp \
    niryoqmodbusbase.cpp \
    trajectoirniryo.cpp

HEADERS += \
    niryoinfo.h \
    poseniryo.h \
    Niryo_global.h \
    niryocontroller.h \
    niryoqmodbusbase.h \
    trajectoirniryo.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target