#-------------------------------------------------
#
# Project created by QtCreator 2018-02-16T23:46:18
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTcpServer
TEMPLATE = app


SOURCES += main.cpp\
    tcpserver.cpp \
    tcpclient.cpp

HEADERS  += \
    tcpserver.h \
    tcpclient.h

FORMS    += \
    tcpserver.ui \
    tcpclient.ui

DISTFILES += \
    README
