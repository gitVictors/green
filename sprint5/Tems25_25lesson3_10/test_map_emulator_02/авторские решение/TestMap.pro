QT += testlib
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

MAP_PATH = ../qt_map

INCLUDEPATH += $$MAP_PATH

SOURCES +=  tst_testmap.cpp \
            $$MAP_PATH//mainwindow.cpp

HEADERS +=  \
    $$MAP_PATH//mainwindow.h \
    $$MAP_PATH//model.h

FORMS += \
    $$MAP_PATH//mainwindow.ui