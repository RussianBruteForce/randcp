#-------------------------------------------------
#
# Project created by QtCreator 2013-05-24T16:09:32
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = randcp
CONFIG   += console c++11
CONFIG   -= app_bundle
QMAKE_LIBS += -lgomp -lpthread
QMAKE_CXXFLAGS += -fopenmp -D_GLIBCXX_PARALLEL
LIBS += -lgomp -lpthread

TEMPLATE = app


SOURCES += main.cpp

HEADERS +=
