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
    src/serialportdialog.cpp \
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
    src/serialportdialog.h \
    src/xToolsBaudRateComboBox.h \
    src/xToolsComboBox.h \
    src/xToolsDataBitsComboBox.h \
    src/xToolsFlowControlComboBox.h \
    src/xToolsParityComboBox.h \
    src/xToolsPortNameComboBox.h \
    src/xToolsStopBitsComboBox.h

FORMS += \
    src/mainwindow.ui \
    src/serialportdialog.ui

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}


build_type =
CONFIG(debug, debug|release) {
    build_type = debug
} else {
    build_type = release
}

DESTDIR     = $$build_type/out
OBJECTS_DIR = $$build_type/obj
MOC_DIR     = $$build_type/moc
RCC_DIR     = $$build_type/rcc
UI_DIR      = ./ui

INCLUDEPATH += ./include
INCLUDEPATH += src

include($$PWD/QtGlobalEvent/GlobalMouseKey/GlobalMouseKey.pri)
INCLUDEPATH += $$PWD/QtGlobalEvent/GlobalMouseKey



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/input_lite/build/release/ -linput_lite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/input_lite/build/debug/ -linput_lite

INCLUDEPATH += $$PWD/input_lite/include
DEPENDPATH += $$PWD/input_lite/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/input_lite/build/release/libinput_lite.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/input_lite/build/debug/libinput_lite.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/input_lite/build/release/input_lite.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/input_lite/build/debug/input_lite.lib
