cmake_minimum_required(VERSION 3.8)

project(flog)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.h
)

add_library(flog ${SRC})

add_compile_options(-Wall -Wextra -Wpedantic -O2 -march=native -flto)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
