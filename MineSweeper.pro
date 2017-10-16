#-------------------------------------------------
#
# Project created by QtCreator 2017-10-15T17:09:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MineSweeper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameboard.cpp \
    gamebutton.cpp

HEADERS  += mainwindow.h \
    gameboard.h \
    gamebutton.h

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    gameboardstyle.qss
