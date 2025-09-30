QT = core

CONFIG += c++23 cmdline

# Строгие флаги компиляции
QMAKE_CXXFLAGS += -Werror  -Wall    -Wextra -pedantic
# QMAKE_CXXFLAGS += -Wconversion -Wsign-conversion
# QMAKE_CXXFLAGS += -Wshadow -Wunused -Wmissing-field-initializers
# QMAKE_CXXFLAGS += -Wold-style-cast -Wnarrowing

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
