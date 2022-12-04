set(UTILS_TESTS utils_tests.cpp)
enable_testing()

add_executable(utils_tests ${UTILS_TESTS})

target_link_libraries(utils_tests 
        GTest::GTest
        gtest_main
        utils)

add_test(test_function_convert_string_to_vector utils_tests)
add_test(test_function_remove_leading_zeros utils_tests)
add_test(test_function_add_trailing_zeros utils_tests)



