set(RATIONAL_TESTS rational_tests.cpp)
enable_testing()

add_executable(rational_tests ${RATIONAL_TESTS})

target_link_libraries(rational_tests 
        GTest::GTest
        gtest_main
        rational
)
