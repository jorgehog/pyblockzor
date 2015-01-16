TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(../defaults.pri)

LIBS += -L../lib -lpyblockzor_core

SOURCES += testsmain.cpp

INCLUDEPATH += ../include
