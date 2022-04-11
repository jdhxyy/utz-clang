TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    ../../clib/crc16-clang/crc16.c \
    ../../clib/tzmalloc/bget.c \
    ../../clib/tzmalloc/tzmalloc.c \
    ../../utzcommon.c \
    ../../utzehp.c \
    ../../utzflp.c \
    ../../utznlp.c \
    ../../utzccp.c \
    ../../utzadhoccmp.c \
    ../../clib/scunit-clang/scunit.c \
    ../../clib/tzbox/tzbox.c \
    ../../clib/lagan-clang/lagan.c

INCLUDEPATH += ../../ \
    ../../clib/crc16-clang \
    ../../clib/tzmalloc \
    ../../clib/scunit-clang \
    ../../clib/tzbox \
    ../../clib/tztype-clang \
    ../../clib/lagan-clang

HEADERS += \
    ../../clib/crc16-clang/crc16.h \
    ../../clib/tzmalloc/bget.h \
    ../../clib/tzmalloc/tzmalloc.h \
    ../../utz.h \
    ../../utzcmp.h \
    ../../utzcommon.h \
    ../../utzehp.h \
    ../../utzflp.h \
    ../../utznlp.h \
    ../../utzccp.h \
    ../../utzadhoccmp.h \
    ../../clib/scunit-clang/scunit.h \
    ../../clib/tzbox/tzbox.h \
    ../../clib/tztype-clang/tztype.h \
    ../../clib/lagan-clang/lagan.h
