#include <gtest/gtest.h>

#include <utils.h>

TEST(utils_tests, test_gcd_function) {
    long long expected1 = 2;
    long long gcd1 = utils::gcd(4,2);
    ASSERT_EQ(gcd1, expected1);

    long long expected2 = 1;
    long long gcd2 = utils::gcd(13,7);
    ASSERT_EQ(gcd2, expected2);

    long long expected3 = 5;
    long long gcd3 = utils::gcd(15,10);
    ASSERT_EQ(gcd3, expected3);
}

TEST(utils_tests, test_lcm_function) {
    long long expected1 = 4;
    long long gcd1 = utils::gcd(4,2);
    ASSERT_EQ(gcd1, expected1);

    long long expected2 = 13 * 7;
    long long gcd2 = utils::gcd(13,7);
    ASSERT_EQ(gcd2, expected2);

    long long expected3 = 30;
    long long gcd3 = utils::gcd(15,10);
    ASSERT_EQ(gcd3, expected3);
}
