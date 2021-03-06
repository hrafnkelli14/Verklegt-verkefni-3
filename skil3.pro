#-------------------------------------------------
#
# Project created by QtCreator 2015-12-09T14:42:33
#
#-------------------------------------------------

QT       += sql core gui network webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = skil3
CONFIG += c++11
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    computer.cpp \
    dbmanager.cpp \
    person.cpp \
    requestprocessor.cpp \
    personedit.cpp \
    computeredit.cpp \
    relationwindow.cpp \
    aboutwindow.cpp \
    infowindow.cpp \
    helpwindow.cpp

HEADERS  += mainwindow.h \
    computer.h \
    dbmanager.h \
    person.h \
    requestprocessor.h \
    personedit.h \
    computeredit.h \
    relationwindow.h \
    aboutwindow.h \
    infowindow.h \
    helpwindow.h

FORMS    += mainwindow.ui \
    personedit.ui \
    computeredit.ui \
    relationwindow.ui \
    aboutwindow.ui \
    infowindow.ui \
    helpwindow.ui

win32:RC_ICONS += icon.ico
