cmake_minimum_required(VERSION 3.30)
project(colorscheme_util)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)

include_directories("include")

add_executable(colorscheme_util
    src/main.cpp
    src/colorscheme.cpp
    src/formatConverter.cpp)

target_link_libraries(colorscheme_util PRIVATE 
    ${OpenCV_LIBS})
