cmake_minimum_required(VERSION 3.11)

project(negate CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(negate
        main.cpp
        img_lib.cpp
        ppm_image.cpp
)
target_link_libraries(negate -lstdc++)
