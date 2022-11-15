#include <gtest/gtest.h>

#include <utils.h>

TEST(utils_tests, test_function_convert_string_to_vector) {
    std::vector<int> expected = {3, 2, 1};
    ASSERT_EQ(utils::make_vector_from_string("123"), expected);
}

TEST(utils_tests, test_function_remove_leading_zeros) {
    std::vector<int> expected = {1, 2, 3};
    std::vector<int> input = {1, 2, 3, 0, 0, 0};
    utils::remove_leading_zeros(input);
    ASSERT_EQ(input.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(input[i], expected[i]);
    }
}

TEST(utils_tests, test_function_add_trailing_zeros) {
    std::vector<int> expected = {0, 0, 0, 1, 2, 3};
    std::vector<int> input = {1, 2, 3};
    utils::add_trailing_zeros(input, 3);
    ASSERT_EQ(input.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(input[i], expected[i]);
    }
}

TEST(utils_tests, test_compare_vectors) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {2, 3, 4};
    ASSERT_TRUE(utils::compare_two_positive_vectors(v1, v2, [](int a, int b){
        return a < b;
    }));

    std::vector<int> v3 = {5, 4, 3};
    ASSERT_TRUE(utils::compare_two_positive_vectors(v3, v1, [](int a, int b){
        return a > b;
    }));
}