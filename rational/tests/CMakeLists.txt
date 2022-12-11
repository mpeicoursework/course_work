set(RATIONAL_TESTS rational_tests.cpp)
enable_testing()

add_executable(RationalTests ${RATIONAL_TESTS})

target_link_libraries(RationalTests 
        GTest::GTest
        gtest_main
        rational
)

add_test(RationalTests RationalTests)
