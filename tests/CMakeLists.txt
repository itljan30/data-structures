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
endforeach()

add_test(NAME DynamicArrayTest COMMAND DynArrTest)
add_test(NAME LinkedListTest COMMAND LinkedListTest)
