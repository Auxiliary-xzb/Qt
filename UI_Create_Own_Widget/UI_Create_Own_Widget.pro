#-------------------------------------------------
#
# Project created by QtCreator 2018-02-06T17:22:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UI_Create_Own_Widget
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mywidget.cpp

HEADERS  += widget.h \
    mywidget.h

FORMS    += widget.ui

DISTFILES += \
    README
