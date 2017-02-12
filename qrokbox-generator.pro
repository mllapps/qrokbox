#-------------------------------------------------
#
# Project created by QtCreator 2016-12-16T07:29:36
#
#-------------------------------------------------

VERSION = 1.0.0-beta
DEFINES += VERSION_STRING='\\\"$${VERSION}\\\"'

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qrokbox
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    mrokbox.cpp \
    mproducer.cpp \
    mapplication.cpp \
    lib/metadata/qexifimageheader.cpp \
    lib/metadata/qmetadata.cpp \
    widgets/qroundprogressbar.cpp \
    console.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    mrokbox.h \
    mproducer.h \
    mapplication.h \
    lib/metadata/qexifimageheader.h \
    lib/metadata/qmetadata.h \
    widgets/qroundprogressbar.h \
    console.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

RESOURCES += \
    mainwindow.qrc

INCLUDEPATH += lib widgets

#CONFIG-=app_bundle

  DISTFILES += \
    resource.rc

win32:{
  RC_FILE = resources.rc
}
