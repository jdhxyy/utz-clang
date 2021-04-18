TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    ../../lib/crc16-clang/crc16.c \
    ../../lib/tzmalloc/bget.c \
    ../../lib/tzmalloc/tzmalloc.c \
    ../../utzcommon.c \
    ../../utzehp.c \
    ../../utzflp.c \
    ../../utznlv1.c \
    ../../lib/scunit-clang/scunit.c \
    ../../lib/tzbox/tzbox.c

INCLUDEPATH += ../../ \
    ../../lib/crc16-clang \
    ../../lib/tzmalloc \
    ../../lib/scunit-clang \
    ../../lib/tzbox

HEADERS += \
    ../../lib/crc16-clang/crc16.h \
    ../../lib/tzmalloc/bget.h \
    ../../lib/tzmalloc/tzmalloc.h \
    ../../utz.h \
    ../../utzcmp.h \
    ../../utzcommon.h \
    ../../utzehp.h \
    ../../utzflp.h \
    ../../utznlv1.h \
    ../../lib/scunit-clang/scunit.h \
    ../../lib/tzbox/tzbox.h
