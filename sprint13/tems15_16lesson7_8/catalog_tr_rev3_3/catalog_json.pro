QT = core

CONFIG += c++20 cmdline

# Строгие флаги компиляции
# QMAKE_CXXFLAGS += -Werror  -Wall    -Wextra -pedantic
# QMAKE_CXXFLAGS += -Wconversion -Wsign-conversion
# QMAKE_CXXFLAGS += -Wshadow -Wunused -Wmissing-field-initializers
# QMAKE_CXXFLAGS += -Wold-style-cast -Wnarrowing

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        domain.cpp \
        geo.cpp \
        json.cpp \
        json_builder.cpp \
        json_reader.cpp \
        main.cpp \
        map_renderer.cpp \
        request_handler.cpp \
        svg.cpp \
        transport_catalogue.cpp \
        transport_router.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    domain.h \
    geo.h \
    graph.h \
    json.h \
    json_builder.h \
    json_reader.h \
    map_renderer.h \
    ranges.h \
    request_handler.h \
    router.h \
    svg.h \
    transport_catalogue.h \
    transport_router.h
