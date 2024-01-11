cmake_minimum_required(VERSION 3.21)

project(SoftView VERSION 0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(lib)
if (NOT DEFINED EMSCRIPTEN)
    add_subdirectory(CLI)
endif()