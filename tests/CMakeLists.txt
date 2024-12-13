project(tests)

add_executable(DynArrTest t_dyn_arr.c test_struct.c)
add_executable(LinkedListTest t_linked_list.c test_struct.c)
add_executable(BinaryTreeTest t_binary_tree.c test_struct.c)
add_executable(HashMapTest t_hash_map.c test_struct.c)
add_executable(GraphTest t_graph.c test_struct.c)

set(TEST_EXECUTABLES 
    DynArrTest 
    LinkedListTest
    BinaryTreeTest
    HashMapTest
    GraphTest
)

foreach(test_executable ${TEST_EXECUTABLES})
    target_link_libraries(${test_executable} PRIVATE DataStructures)
    add_test(
        NAME ${test_executable} 
        COMMAND valgrind --leak-check=full --track-origins=yes $<TARGET_FILE:${test_executable}>
    )
endforeach()
