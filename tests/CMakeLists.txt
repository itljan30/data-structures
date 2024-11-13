project(tests)

set(TEST_EXECUTABLES DynArrTest LinkedListTest)

add_executable(DynArrTest
    t_dyn_arr.c
    ../src/dyn_arr.c
)

add_executable(LinkedListTest
    t_linked_list.c
    ../src/linked_list.c
    ../src/node.c
)

foreach(test_executable ${TEST_EXECUTABLES})
    target_include_directories(${test_executable} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    
    add_test(NAME ${test_executable} COMMAND
        valgrind --leak-check=full --track-origins=yes $<TARGET_FILE:${test_executable}>
    )

endforeach()
