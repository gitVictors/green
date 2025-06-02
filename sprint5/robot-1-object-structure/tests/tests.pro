########
MOCK_LIB=../../../../mocks_library
########

QT += testlib
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += qt warn_on depend_includepath testcase

CONFIG += c++20

SUBMISSION_PATH = ../submission

INCLUDEPATH += $$SUBMISSION_PATH

TEMPLATE = app

SOURCES += \
        tests.cpp \
        $$SUBMISSION_PATH/mainwindow.cpp \
        $$SUBMISSION_PATH/utility/painter.cpp

HEADERS += \
        utils.h \
        $$SUBMISSION_PATH/context.h \
        $$SUBMISSION_PATH/character.h \
        $$SUBMISSION_PATH/characters.h \
        $$SUBMISSION_PATH/field.h \
        $$SUBMISSION_PATH/field_elements.h \
        $$SUBMISSION_PATH/game.h \
        $$SUBMISSION_PATH/mainwindow.h \
        $$SUBMISSION_PATH/object.h \
        $$SUBMISSION_PATH/objects.h \
        $$SUBMISSION_PATH/utility/painter.h \
        $$SUBMISSION_PATH/player.h \
        $$SUBMISSION_PATH/utility/geometry.h \
        $$SUBMISSION_PATH/utility/random.h \
        $$SUBMISSION_PATH/utility/timer.h \
        $$SUBMISSION_PATH/utility/sprites.h \
        $$SUBMISSION_PATH/utility/utility.h

FORMS += \
        $$SUBMISSION_PATH/mainwindow.ui

RESOURCES += \
        $$SUBMISSION_PATH/game.qrc