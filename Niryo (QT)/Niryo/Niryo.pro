QT -= gui
QT += network serialbus

TEMPLATE = lib
DEFINES += NIRYO_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    axis.cpp \
    controller.cpp \
    niryo.cpp \
    stats.cpp \
    trajectory.cpp

HEADERS += \
    Niryo_global.h \
    axis.h \
    controller.h \
    enums.h \
    niryo.h \
    stats.h \
    trajectory.h \

    $$PWD/../ModbusUtil/modbusutil.h


# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L. -lModbusUtil

INCLUDEPATH += $$PWD/../ModbusUtil
DEPENDPATH += $$PWD/../ModbusUtil
