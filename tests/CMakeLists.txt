project(tests)

add_executable(DynArrTest t_dyn_arr.c)
add_executable(LinkedListTest t_linked_list.c)
add_executable(BinaryTreeTest t_binary_tree.c)

set(TEST_EXECUTABLES 
    DynArrTest 
    LinkedListTest
    BinaryTreeTest
)

foreach(test_executable ${TEST_EXECUTABLES})
    target_link_libraries(${test_executable} PRIVATE DataStructures)
    add_test(
        NAME ${test_executable} 
        COMMAND valgrind --leak-check=full --track-origins=yes $<TARGET_FILE:${test_executable}>
    )
endforeach()
