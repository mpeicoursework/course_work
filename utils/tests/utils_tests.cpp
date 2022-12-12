#include <gtest/gtest.h>

#include <utils.h>

#include <vector>
#include <tuple>

TEST(UtilsTests, test_function_convert_string_to_vector) {
    std::vector<int> expected = {3, 2, 1};
    ASSERT_EQ(utils::make_vector_from_string("123"), expected);
}

TEST(UtilsTests, test_function_remove_leading_zeros) {
    std::vector<int> expected = {1, 2, 3};
    std::vector<int> input = {1, 2, 3, 0, 0, 0};
    utils::remove_leading_zeros(input);
    ASSERT_EQ(input.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(input[i], expected[i]);
    }
}

TEST(UtilsTests, test_function_add_trailing_zeros) {
    std::vector<int> expected = {0, 0, 0, 1, 2, 3};
    std::vector<int> input = {1, 2, 3};
    utils::add_trailing_zeros(input, 3);
    ASSERT_EQ(input.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(input[i], expected[i]);
    }
}

TEST(UtilsTests, test_compare_vectors) {
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

class ParamerizedFixtureForTest : public ::testing::TestWithParam<std::tuple<std::vector<int>, std::string>> {};

TEST_P(ParamerizedFixtureForTest, test_convert_vec_int_to_string) {
    auto [vec, expected_res] = GetParam();
    EXPECT_EQ(utils::make_string_from_vector(vec), expected_res);
}

INSTANTIATE_TEST_SUITE_P(
    UtilsTests,
    ParamerizedFixtureForTest,
    ::testing::Values(
        std::make_tuple(std::vector<int>{4, 3, 2, 1}, "1234"),
        std::make_tuple(std::vector<int>{5, 1, 7, 8}, "8715"),
        std::make_tuple(std::vector<int>{5, 0, 1, 2}, "2105")           
    )
);