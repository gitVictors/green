QT += widgets  testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

MAP_PATH = ../../test_map_emulator/submission
INCLUDEPATH += $$MAP_PATH



SOURCES += tst_testmapemulator.cpp \
../../test_map_emulator/submission/mainwindow.cpp

HEADERS += ../../test_map_emulator/submission/mainwindow.h

FORMS +=  \
    $$MAP_PATH//mainwindow.ui
