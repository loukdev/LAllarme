#-------------------------------------------------
#
# Project created by QtCreator 2015-01-15T21:41:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LAllarme
TEMPLATE = app


SOURCES += \
    AboutLAllarme.cpp \
    LAlla.cpp \
    LAllarme.cpp \
    LAllarmeOptions.cpp \
    LAllarmeWidget.cpp \
    LChronoWidget.cpp \
    LTimerWidget.cpp \
    main.cpp

HEADERS  += \
    AboutLAllarme.h \
    LAlla.h \
    LAllarme.h \
    LAllarmeOptions.h \
    LAllarmeWidget.h \
    LChronoWidget.h \
    LTimerWidget.h

FORMS    += \
    lallarme_options.ui \
    lallarme.ui \
    about_lallarme.ui

DISTFILES += \
    lallarme_en.ts
