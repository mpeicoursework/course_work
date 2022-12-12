set(UTILS_TESTS utils_tests.cpp)
enable_testing()

add_executable(UtilsTests ${UTILS_TESTS})

target_link_libraries(UtilsTests
        GTest::GTest
        gtest_main
        utils)

add_test(UtilsTests UtilsTests)



