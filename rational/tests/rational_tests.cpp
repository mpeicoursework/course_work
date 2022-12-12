#include <gtest/gtest.h>

#include <rational.h>

#include <iostream>
#include <tuple>

class ParametrizedTestFixtureForBigIntClassArithmeticOperator :
    public ::testing::Test, public ::testing::WithParamInterface<std::tuple<std::string, std::string, std::string>> {
protected:
    void SetUp() override {
        auto t = GetParam();
        std::string s_num1 = std::get<0>(t);
        std::string s_num2 = std::get<1>(t);
        std::string s_expected_res = std::get<2>(t);
        num1_ = rational::rational(s_num1);
        num2_ = rational::rational(s_num2);
        expected_res_ = rational::rational(s_expected_res);
    }

    void TearDown() override {} 
    rational::rational num1_;
    rational::rational num2_;
    rational::rational expected_res_;
};

class TestOperatorPlusForRational : public ParametrizedTestFixtureForBigIntClassArithmeticOperator {};
class TestOperatorMultiplication : public ParametrizedTestFixtureForBigIntClassArithmeticOperator {};

TEST_P(TestOperatorPlusForRational, TestOperatorPlus) {
    EXPECT_EQ(num1_ + num2_, expected_res_);
}

TEST_P(TestOperatorMultiplication, TestOperatorMultiplication) {
    EXPECT_EQ(num1_ * num2_, expected_res_);
}

INSTANTIATE_TEST_SUITE_P(
    RationalTests,
    TestOperatorPlusForRational,
    ::testing::Values(
        std::make_tuple("1/6", "2/6", "1/2"),
        std::make_tuple("1/2", "1/2", "1/1")
    )
);

INSTANTIATE_TEST_SUITE_P(
    RationalTests,
    TestOperatorMultiplication,
    ::testing::Values(
        std::make_tuple("1/6", "2/6", "1/18")
    )
);


class TestFixtureForGetDoubleMethod : public ::testing::TestWithParam<std::tuple<rational::rational, double>> {};

TEST_P(TestFixtureForGetDoubleMethod, DoubleMethodTest) {
    auto [num, expected_res] = GetParam();
    EXPECT_EQ(num.get_double(), expected_res);
}

INSTANTIATE_TEST_SUITE_P(
    RationalTests,
    TestFixtureForGetDoubleMethod,
    ::testing::Values(
        std::make_tuple(rational::rational("1/4"), 0.25)
    )
);
