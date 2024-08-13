QT       += core gui serialbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    niryoinfo.cpp \
    poseniryo.cpp \
    testinterface2.cpp \
    niryocontroller.cpp \
    niryoqmodbusbase.cpp \
    trajectoirniryo.cpp

HEADERS += \
    niryoinfo.h \
    poseniryo.h \
    testinterface2.h \
    niryocontroller.h \
    niryoqmodbusbase.h \
    trajectoirniryo.h

FORMS += \
    testinterface2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/../ModbusUtil/ -lModbusUtil

INCLUDEPATH += $$PWD/../ModbusUtil
DEPENDPATH += $$PWD/../ModbusUtil
