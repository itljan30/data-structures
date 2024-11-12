project(tests)

set(TEST_EXECUTABLES DynArrTest)

add_executable(DynArrTest
    t_dyn_arr.c
    ../src/dyn_arr.c
)

foreach(test_executable ${TEST_EXECUTABLES})
    target_include_directories(${test_executable} PRIVATE ${CMAKE_SOURCE_DIR}/include)
endforeach()

add_test(NAME DynamicArrayTest COMMAND DynArrTest)
