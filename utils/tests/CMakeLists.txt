set(UTILS_TESTS utils_tests.cpp)
enable_testing()

add_executable(utils_tests ${UTILS_TESTS})

target_link_libraries(utils_tests 
        GTest::GTest
        gtest_main
        utils)

add_test(utils_gtest utils_tests)



