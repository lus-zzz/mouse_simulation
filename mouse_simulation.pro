QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/CH9329.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/xToolsBaudRateComboBox.cpp \
    src/xToolsComboBox.cpp \
    src/xToolsDataBitsComboBox.cpp \
    src/xToolsFlowControlComboBox.cpp \
    src/xToolsParityComboBox.cpp \
    src/xToolsPortNameComboBox.cpp \
    src/xToolsStopBitsComboBox.cpp

HEADERS += \
    src/CH9329.h \
    src/mainwindow.h \
    src/xToolsBaudRateComboBox.h \
    src/xToolsComboBox.h \
    src/xToolsDataBitsComboBox.h \
    src/xToolsFlowControlComboBox.h \
    src/xToolsParityComboBox.h \
    src/xToolsPortNameComboBox.h \
    src/xToolsStopBitsComboBox.h

FORMS += \
    src/mainwindow.ui

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

INCLUDEPATH += src

include($$PWD/QtGlobalEvent/GlobalMouseKey/GlobalMouseKey.pri)
INCLUDEPATH += $$PWD/QtGlobalEvent/GlobalMouseKey



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/input_lite/ -linput_lite

INCLUDEPATH += $$PWD/input_lite/include
DEPENDPATH += $$PWD/input_lite/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/input_lite/input_lite.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/input_lite/libinput_lite.a
