cmake_minimum_required(VERSION 3.15)
project(DataStructures)

add_library(DataStructures SHARED
    src/binary_tree.c
    src/dyn_arr.c
    src/hash_map.c
    src/linked_list.c
    src/node.c
)
target_include_directories(DataStructures PUBLIC ${CMAKE_SOURCE_DIR}/include)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
    enable_testing()
    add_subdirectory(tests)
endif()
