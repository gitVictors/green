cmake_minimum_required(VERSION 3.14)

project(tabl LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Явно указываем версию Qt
set(QT_VERSION 6.5.0 CACHE STRING "Qt version to use")
set(CMAKE_PREFIX_PATH "/media/E6C635BBC6358CB5/Qt/6.5.0;${CMAKE_PREFIX_PATH}")


find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)

add_executable(tabl
  main.cpp
  common.h
  structures.cpp
  test_runner_p.h
)
target_link_libraries(tabl Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS tabl
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
