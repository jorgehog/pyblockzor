TEMPLATE = lib

TARGET = ../lib/pyblockzor_core

include(../defaults.pri)

SOURCES += \
    dataset.cpp

HEADERS += \
    dataset.h

LIBS += -fopenmp


QMAKE_PRE_LINK += $(MKDIR) $$PWD/../lib $$shadowed($$PWD)/../lib


