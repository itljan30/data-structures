set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(DataStructures
    main.c
    dyn_arr.c
)

target_include_directories(DataStructures PRIVATE ${CMAKE_SOURCE_DIR}/include)

