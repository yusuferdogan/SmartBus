#-------------------------------------------------
#
# Project created by QtCreator 2015-07-27T09:31:53
#
#-------------------------------------------------


DEFINES += SENSORAPI_DLL

QT       += core positioning serialport network xml

QT       -= gui

TARGET = SmartBus
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    gpsmodule.cpp \
    sensordevice.cpp \
    qftp.cpp \
    qurlinfo.cpp

HEADERS += \
    gpsmodule.h \
    sensordevice.h \
    qftp.h \
    qurlinfo.h



LIBS += -L$$PWD/../../IRMA_MATRIX_SDK_for_i686/lib/slackware/iris/sensor-api/shared/ -lIrmaMatrix

INCLUDEPATH += $$PWD/../../IRMA_MATRIX_SDK_for_i686/include/iris/sensor-api/
DEPENDPATH += $$PWD/../../IRMA_MATRIX_SDK_for_i686/include/iris/sensor-api/

LIBS += -L$$PWD/../../IRMA_MATRIX_SDK_for_i686/lib/slackware/3rd-party/boost-1_42/shared/ -lboost_system \
-lboost_filesystem \
-lboost_thread \
-lboost_regex \
-lboost_date_time \
-ldl

INCLUDEPATH += $$PWD/../../IRMA_MATRIX_SDK_for_i686/include/3rd-party/boost-1.42
DEPENDPATH += $$PWD/../../IRMA_MATRIX_SDK_for_i686/include/3rd-party/boost-1.42
