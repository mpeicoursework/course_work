set(BIG_INT_TESTS big_int_tests.cpp)
enable_testing()

add_executable(BigIntTests ${BIG_INT_TESTS})

target_link_libraries(BigIntTests
        GTest::GTest
        gtest_main
        big_int
)

add_test(BigIntTests BigIntTests)