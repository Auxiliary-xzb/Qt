#-------------------------------------------------
#
# Project created by QtCreator 2018-02-20T20:24:24
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTcp_Transfer_File
TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    client.cpp

HEADERS  += \
    server.h \
    client.h

FORMS    += \
    server.ui \
    client.ui

DISTFILES += \
    README
