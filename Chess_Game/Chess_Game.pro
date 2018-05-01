#-------------------------------------------------
#
# Project created by QtCreator 2018-02-15T19:28:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess_Game
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mypiece.cpp

HEADERS  += widget.h \
    mypiece.h

FORMS    += widget.ui

RESOURCES += \
    picture.qrc
