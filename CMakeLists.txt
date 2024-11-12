cmake_minimum_required(VERSION 3.15)
project(DataStructures)

add_library(DataStructures SHARED
    src/dyn_arr.c
)
target_include_directories(DataStructures PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (default: Debug)")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    enable_testing()
    add_subdirectory(tests)
endif()
