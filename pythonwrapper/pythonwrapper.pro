TEMPLATE = lib

TARGET = ../lib/pyblockzor_python

include(../defaults.pri)

SOURCES += pythonwrapper.cpp

HEADERS += pythonwrapper.h

INCLUDEPATH += $$PWD/../include /usr/include/python2.7

LIBS += -L$$PWD/../lib -lpyblockzor -lboost_python -lboost_numpy

QMAKE_POST_LINK += bash $$PWD/build.sh $$PWD $$shadowed($$PWD)

QMAKE_CLEAN += $$shadowed($$PWD)/../build/lib.linux-x86_64-2.7/pyblockzor.so \
    $$shadowed($$PWD)/../build/temp.linux-x86_64-2.7/pythonwrapper.o

OTHER_FILES += setup.py

DISTFILES += \
    build.sh

