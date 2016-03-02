#-------------------------------------------------
#
# Project created by QtCreator 2016-02-26T14:06:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimonGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Game.cpp

HEADERS  += mainwindow.h \
    Game.h \
    Game.h

FORMS    += mainwindow.ui

DISTFILES += \
    README.txt
