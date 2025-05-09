########
MOCK_LIB=../../../../mocks_library
########

QT += testlib
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += qt warn_on depend_includepath testcase

CONFIG += c++17

SUBMISSION_PATH = ../submission

INCLUDEPATH += $$SUBMISSION_PATH

TEMPLATE = app

SOURCES +=  tests.cpp \
    $$SUBMISSION_PATH/calculator.cpp \
    $$SUBMISSION_PATH/mainwindow.cpp
    $$SUBMISSION_PATH/main.cpp

HEADERS +=  \
    $$SUBMISSION_PATH/calculator.h \
    $$SUBMISSION_PATH/mainwindow.h

FORMS += \
    $$SUBMISSION_PATH/mainwindow.ui
