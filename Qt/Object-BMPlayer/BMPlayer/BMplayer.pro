#-------------------------------------------------
#
# Project created by QtCreator 2011-02-09T12:59:48
#
#-------------------------------------------------

QT       += core gui

TARGET = BMPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bmplayerwidget.cpp \
    openurldialog.cpp \
    aboutbmysoftdialog.cpp \
    internet_radio.cpp \
    contributions.cpp

HEADERS  += mainwindow.h \
    bmplayerwidget.h \
    openurldialog.h \
    aboutbmysoftdialog.h \
    internet_radio.h \
    contributions.h

FORMS    += mainwindow.ui \
    openurldialog.ui \
    aboutbmysoftdialog.ui \
    internet_radio.ui \
    contributions.ui

RESOURCES += \
    image.qrc

win32 {

RC_FILE = BMPlayer.rc

}

RC_FILE = BMPlayer_UNIX.rc
