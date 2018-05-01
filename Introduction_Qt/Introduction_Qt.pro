#-------------------------------------------------
#
# Project created by QtCreator 2018-01-21T14:59:52
#
#-------------------------------------------------

#模块，这里使用的是qmake所需要的模块。
#在每个头文件加入时，在qmake时会去查询模块。
#
QT       += core gui

#该语句是为了兼容Qt4
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


#在makefile中，文件的命令格式如下
#target... : prerequisites ...
#   command
#这里的target就是最后的程序名称。
TARGET = Introduction_Qt

#指定Makefile的类型为app
TEMPLATE = app

#源文件集合
SOURCES += main.cpp\
        widget.cpp

#头文件集合
HEADERS  += widget.h

#其他文件
DISTFILES += \
    README
