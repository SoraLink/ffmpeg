#-------------------------------------------------
#
# Project created by QtCreator 2017-06-21T10:44:06
#
#-------------------------------------------------

QT       += core gui multimedia

INCLUDEPATH +=D:\player\player\include


LIBS +=-LD:\player\player\lib\ -lavcodec
LIBS +=-LD:\player\player\lib\ -lavdevice
LIBS +=-LD:\player\player\lib\ -lavfilter
LIBS +=-LD:\player\player\lib\ -lavformat
LIBS +=-LD:\player\player\lib\ -lavutil
LIBS +=-LD:\player\player\lib\ -lpostproc
LIBS +=-LD:\player\player\lib\ -lswresample
LIBS +=-LD:\player\player\lib\ -lswscale

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = player
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    xffmpeg.cpp \
    videowidget.cpp \
    xvideothread.cpp \
    xslider.cpp \
    xaudioplay.cpp \
    wavefile.cpp \
    widget.cpp

HEADERS += \
        mainwindow.h \
    xffmpeg.h \
    videowidget.h \
    xvideothread.h \
    xslider.h \
    xaudioplay.h \
    wavefile.h \
    widget.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    res.qrc
