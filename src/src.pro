include($$PWD/../propagator.pri)

TEMPLATE = app
TARGET = propagator
DESTDIR = $$OUTPUT_DIR/bin

DEPENDPATH += .
INCLUDEPATH += .

SOURCES += main.cpp

include($$PWD/src.pri)
