#-------------------------------------------------
#
# Project created by QtCreator 2016-12-16T07:29:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qrokbox
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mrokbox.cpp \
    mproducer.cpp

HEADERS  += mainwindow.h \
    mrokbox.h \
    mproducer.h

FORMS    += mainwindow.ui

RESOURCES += \
    mainwindow.qrc
