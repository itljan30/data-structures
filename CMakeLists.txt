cmake_minimum_required(VERSION 3.15)
project(DataStructures)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (default: Debug)")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    enable_testing()
    add_subdirectory(tests)
endif()

add_subdirectory(src)
