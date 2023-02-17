QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Serial_Demo
TEMPLATE = app

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Serial/crc8_crc16.cpp \
    Serial/protocol.cpp \
    Serial/serial.cpp \
    Serial/serial_system.cpp \
    main.cpp \
    serial_demo.cpp

DISTFILES += \
    lib/dhdms64.lib \
    lib/drdms64.lib

FORMS += \
    serial_demo.ui

HEADERS += \
    Serial/crc8_crc16.h \
    Serial/protocol.h \
    Serial/serial.h \
    Serial/serial_system.h \
    dhdc.h \
    drdc.h \
    serial_demo.h

#LIBS += \
 #   lib/dhdms64.lib \
  #  lib/drdms64.lib

#DEPENDPATH += lib
