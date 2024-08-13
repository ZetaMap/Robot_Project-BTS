QT       += core gui network serialbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    ihmglobale.cpp \
    production.cpp

HEADERS += \
    ihmglobale.h \
    production.h \
    projet.h \
    $$PWD/../Niryo/axis.h \
    $$PWD/../Niryo/controller.h \
    $$PWD/../Niryo/enums.h \
    $$PWD/../Niryo/niryo.h \
    $$PWD/../Niryo/stats.h \
    $$PWD/../Niryo/trajectory.h \
    $$PWD/../Fanuc/fanuc.h \
    $$PWD/../Convoyeur/convoyeur.h \
    $$PWD/../Afficheur/afficheur.h \
    $$PWD/../ModbusUtil/modbusutil.h

FORMS += \
    ihmglobale.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L./lib \
    -lNiryo \
    -lFanuc \
    -lConvoyeur \
    -lAfficheur \
    -lModbusUtil

INCLUDEPATH += \
    $$PWD/../Niryo \
    $$PWD/../Fanuc \
    $$PWD/../Convoyeur \
    $$PWD/../Afficheur \
    $$PWD/../ModbusUtil

DEPENDPATH += \
    $$PWD/../Niryo \
    $$PWD/../Fanuc \
    $$PWD/../Convoyeur \
    $$PWD/../Afficheur \
    $$PWD/../ModbusUtil
