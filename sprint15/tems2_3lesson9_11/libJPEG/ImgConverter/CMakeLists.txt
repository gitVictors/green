cmake_minimum_required(VERSION 3.11)

project(Negate CXX)
set(CMAKE_CXX_STANDARD 17)

# # Добавьте эту строку перед add_subdirectory
# set(LIBJPEG_DIR "../../jpegsr9f_windows/jpeg-9f/release/" CACHE STRING "LibJPEG directory")
# message(STATUS "LibJPEG set dir is ${LIBJPEG_DIR}")

add_subdirectory(../ImgLib ImgLibBuildDir)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()

add_executable(imgconv main.cpp)
target_include_directories(imgconv PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../ImgLib")
target_link_libraries(imgconv ImgLib ${SYSTEM_LIBS})
