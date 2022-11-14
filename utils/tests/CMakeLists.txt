set(UTILS_TESTS utils_tests.cpp)
enable_testing()

add_executable(utils_tests ${UTILS_TESTS})

target_link_libraries(
        utils_tests
        gtest_main
        utils
)

include(GoogleTest)
gtest_discover_tests(utils_tests)