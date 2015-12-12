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
    computerxpersons.cpp \
    dbmanager.cpp \
    person.cpp \
    personxcomputers.cpp \
    relation.cpp \
    requestprocessor.cpp \
    personedit.cpp \
    computeredit.cpp \
    relationwindow.cpp \
    aboutwindow.cpp \
    infowindow.cpp

HEADERS  += mainwindow.h \
    computer.h \
    computerxpersons.h \
    dbmanager.h \
    person.h \
    personxcomputers.h \
    relation.h \
    requestprocessor.h \
    personedit.h \
    computeredit.h \
    relationwindow.h \
    aboutwindow.h \
    infowindow.h

FORMS    += mainwindow.ui \
    personedit.ui \
    computeredit.ui \
    relationwindow.ui \
    aboutwindow.ui \
    infowindow.ui

win32:RC_ICONS += icon.ico
