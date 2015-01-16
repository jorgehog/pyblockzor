TEMPLATE = lib
CONFIG += plugin

TARGET = ../lib/pyblockzor

include(../defaults.pri)

SOURCES += pythonwrapper.cpp

HEADERS += pythonwrapper.h

INCLUDEPATH += $$PWD/../include /usr/include/python2.7

LIBS += -L$$shadowed($$PWD)/../lib -lpyblockzor_core -lboost_python -lboost_numpy

#Hack to strip the lib prefix for python modules
QMAKE_POST_LINK += mv $$shadowed($$PWD)/../lib/libpyblockzor.so $$shadowed($$PWD)/../lib/pyblockzor.so

