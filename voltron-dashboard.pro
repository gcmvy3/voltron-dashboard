#-------------------------------------------------
#
# Project created by QtCreator 2019-03-25T16:11:55
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = voltron-dashboard
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

LIBS += -lrt

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Threads/BatteryThread.cpp \
    Widgets/BatteryWidget.cpp \
    Threads/ConsoleThread.cpp \
    Widgets/ConsoleWidget.cpp \
    CommunicationManager.cpp \
    Threads/LidarThread.cpp \
    Widgets/LidarWidget.cpp \
    Widgets/LidarRenderer.cpp \
    Threads/CANThread.cpp \
    Widgets/StereoWidget.cpp \
    Threads/StereoThread.cpp \
    Widgets/StereoMemory.cpp \
    Widgets/CANWidget.cpp \
    CANCodeManager.cpp \
    DashboardUtils.cpp \
    CANCode.cpp \
    LoggingManager.cpp \
    Widgets/LoggingWidget.cpp \
    Threads/LoggingThread.cpp \
    SettingsManager.cpp

HEADERS += \
        mainwindow.h \
    Threads/Packets.h \
    Threads/BatteryThread.h \
    Widgets/BatteryWidget.h \
    Threads/ConsoleThread.h \
    Widgets/ConsoleWidget.h \
    CommunicationManager.h \
    Threads/LidarThread.h \
    Widgets/LidarWidget.h \
    Widgets/LidarRenderer.h \
    Threads/CANThread.h \
    Widgets/StereoWidget.h \
    Threads/StereoThread.h \
    Widgets/StereoMemory.h \
    Widgets/CANWidget.h \
    CANCodeManager.h \
    DashboardUtils.h \
    CANCode.h \
    LoggingManager.h \
    Widgets/LoggingWidget.h \
    Threads/LoggingThread.h \
    SettingsManager.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Widgets/Untitled Document
