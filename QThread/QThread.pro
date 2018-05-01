#-------------------------------------------------
#
# Project created by QtCreator 2018-02-21T23:39:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QThread
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mythread_1.cpp \
    mythread_2.cpp

HEADERS  += widget.h \
    mythread_1.h \
    mythread_2.h

FORMS    += widget.ui

DISTFILES += \
    README
