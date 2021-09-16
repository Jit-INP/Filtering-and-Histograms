TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += IDE
DEFINES += "FILTER_SIZ=3"

SOURCES += \
        main.c \
    convol.c \
    filter.c \
    matrix.c \
    median.c \
    hist.c \
    pgmfil.c \
    filutils.c \
    imgoper.c

HEADERS += \
    convol.h \
    filter.h \
    matrix.h \
    utils.h \
    median.h \
    hist.h \
    pgmfil.h \
    filutils.h \
    imgoper.h
