#-------------------------------------------------
#
# Project created by QtCreator 2018-11-27T22:24:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chatClient
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        chatclient.cpp \
    clientSocket.cpp \
    recthread.cpp

HEADERS  += chatclient.h \
    clientSocket.h \
    recthread.h

FORMS    += chatclient.ui

DISTFILES += chatclient.conf \
    chat.log
