cmake_minimum_required(VERSION 3.11)

project(ImgLib CXX)
set(CMAKE_CXX_STANDARD 17)

set(IMGLIB_MAIN_FILES img_lib.h img_lib.cpp)
set(IMGLIB_FORMAT_FILES ppm_image.h ppm_image.cpp)

add_library(ImgLib STATIC ${IMGLIB_MAIN_FILES} 
            ${IMGLIB_FORMAT_FILES})

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()

# создаём динамическую библиотеку из трёх файлов
# цель назовём ImgLibDll
add_library(ImgLibDll SHARED
            imglib_dll_interface.h 
            imglib_dll_interface.cpp
            imglib_dll_defines.h)

# При компоновке динамической библиотеки будем использовать статическую.
# Для этого добавим к ней цель ImgLib
target_link_libraries(ImgLibDll ImgLib ${SYSTEM_LIBS})

# определяем для сборки ImgLibDll макрос IMGLIB_DLL,
# чтобы экспорт функций получился правильным
target_compile_definitions(ImgLibDll PRIVATE IMGLIB_DLL)
