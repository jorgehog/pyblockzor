TEMPLATE = lib

TARGET = ../lib/pyblockzor

include(../defaults.pri)

SOURCES += \
    dataset.cpp

HEADERS += \
    dataset.h


QMAKE_PRE_LINK += $(MKDIR) $$PWD/../lib $$shadowed($$PWD)/../lib


