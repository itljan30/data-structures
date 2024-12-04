cmake_minimum_required(VERSION 3.15)
project(DataStructures)

add_library(DataStructures STATIC
    src/binary_tree.c
    src/dyn_arr.c
    src/hash_map.c
    src/linked_list.c
    src/callbacks.c
    src/graph.c
)
target_include_directories(DataStructures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
    enable_testing()
    add_subdirectory(tests)
endif()
