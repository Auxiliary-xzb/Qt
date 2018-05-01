#-------------------------------------------------
#
# Project created by QtCreator 2018-02-18T20:42:17
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QUdpSocket
TEMPLATE = app


SOURCES += main.cpp \
    udpserver.cpp \
    udpclient.cpp

HEADERS  += \
    udpserver.h \
    udpclient.h

FORMS    += \
    udpserver.ui \
    udpclient.ui

DISTFILES += \
    README
