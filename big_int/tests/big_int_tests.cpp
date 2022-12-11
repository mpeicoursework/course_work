#include <gtest/gtest.h>

#include <big_int.h>

#include <tuple>

class ParametrizedTestFixtureForBigIntArithmeticOperatorsTest :
     public ::testing::Test, public ::testing::WithParamInterface<std::tuple<std::string, std::string, std::string>> {
protected:
    void SetUp() override {
        auto t = GetParam();
        std::string s_num1 = std::get<0>(t);
        std::string s_num2 = std::get<1>(t);
        std::string s_expected_res = std::get<2>(t);
        num1_ = big_int::big_int(s_num1);
        num2_ = big_int::big_int(s_num2);
        expected_res_ = big_int::big_int(s_expected_res);
    }

    void TearDown() override {}
    big_int::big_int num1_;
    big_int::big_int num2_;
    big_int::big_int expected_res_;
};

class TestForOperatorPlus : public ParametrizedTestFixtureForBigIntArithmeticOperatorsTest {};
class TestForOperatorMinus : public ParametrizedTestFixtureForBigIntArithmeticOperatorsTest {};
class TestForOperatorMultiplication : public ParametrizedTestFixtureForBigIntArithmeticOperatorsTest {};
class TestForOperatorDivision : public ParametrizedTestFixtureForBigIntArithmeticOperatorsTest {};
class TestForOperatorRemainder : public ParametrizedTestFixtureForBigIntArithmeticOperatorsTest {};
class TestForGCD : public ParametrizedTestFixtureForBigIntArithmeticOperatorsTest {};
class TestForLCM : public ParametrizedTestFixtureForBigIntArithmeticOperatorsTest {};

TEST_P(TestForOperatorPlus, TestOperatorPlus) {
    EXPECT_EQ(num1_ + num2_, expected_res_);
}

TEST_P(TestForOperatorMinus, TestOperatorMinus) {
    EXPECT_EQ(num1_ - num2_, expected_res_);
}

TEST_P(TestForOperatorMultiplication, TestOperatorMultiplication) {
    EXPECT_EQ(num1_ * num2_, expected_res_);
}

TEST_P(TestForOperatorDivision, TestOperatorDivision) {
    EXPECT_EQ(num1_ / num2_, expected_res_);
}

TEST_P(TestForOperatorRemainder, TestOperatorRemainder) {
    EXPECT_EQ(num1_ % num2_, expected_res_);
}

TEST_P(TestForGCD, TestGCD) {
    EXPECT_EQ(big_int::gcd(num1_, num2_), expected_res_);
}

TEST_P(TestForLCM, TestLCM) {
    std::cout << "lcm = " << big_int::lcm(num1_, num2_) << std::endl;
    EXPECT_EQ(big_int::lcm(num1_, num2_), expected_res_);
}

INSTANTIATE_TEST_SUITE_P(
    BigIntTests,
    TestForOperatorPlus,
    ::testing::Values(
        std::make_tuple("170", "70", "240"),
        std::make_tuple("-170", "240", "70"),
        std::make_tuple("-170", "65", "-105"),
        std::make_tuple("170", "-90", "80"),
        std::make_tuple("-170", "-85", "-255")
    )
);

INSTANTIATE_TEST_SUITE_P(
    BigIntTests,
    TestForOperatorMinus,
    ::testing::Values(
        std::make_tuple("170", "70", "100"),
        std::make_tuple("-170", "-240", "70"),
        std::make_tuple("155", "-240", "395"),
        std::make_tuple("-145", "55", "-200")
    )
);

INSTANTIATE_TEST_SUITE_P(
    BigIntTests,
    TestForOperatorMultiplication,
    ::testing::Values(
        std::make_tuple("10", "12", "120"),
        std::make_tuple("731", "128", "93568"),
        std::make_tuple("-731", "128", "-93568"),
        std::make_tuple("731", "-128", "-93568"),
        std::make_tuple("-731", "-128", "93568"),
        std::make_tuple("13", "9", "117"),
        std::make_tuple("105", "31", "3255")
    )
);

INSTANTIATE_TEST_SUITE_P(
    BigIntTests,
    TestForOperatorDivision,
    ::testing::Values(
        std::make_tuple("10", "5", "2"),
        std::make_tuple("10", "3", "3"),
        std::make_tuple("121", "9", "13"),
        std::make_tuple("140", "-4", "-35"),
        std::make_tuple("-140", "3", "-46"),
        std::make_tuple("80", "2", "40")
    )
);

INSTANTIATE_TEST_SUITE_P(
    BigIntTests,
    TestForOperatorRemainder,
    ::testing::Values(
        std::make_tuple("10", "3", "1"),
        std::make_tuple("121", "9", "4")
    )
);

INSTANTIATE_TEST_SUITE_P(
    BigIntTests,
    TestForGCD,
    ::testing::Values(
        std::make_tuple("48", "36", "12"),
        std::make_tuple("25", "36", "1"),
        std::make_tuple("18", "24", "6"),
        std::make_tuple("42", "56", "14")
    )
);

INSTANTIATE_TEST_SUITE_P(
    BigIntTests,
    TestForLCM,
    ::testing::Values(
        std::make_tuple("8", "10", "40"),
        std::make_tuple("15", "20", "60")
    )
);

class ParametrizedTestFixtureForCompareOperators : 
    public ::testing::Test, public ::testing::WithParamInterface<std::tuple<std::string, std::string>> {
protected:
    void SetUp() override {
        auto t = GetParam();
        std::string s_num1 = std::get<0>(t);
        std::string s_num2 = std::get<1>(t);
        num1_ = big_int::big_int(s_num1);
        num2_ = big_int::big_int(s_num2);
    }

    void TearDown() override {}
    big_int::big_int num1_;
    big_int::big_int num2_;
};

class TestOperatorLess : public ParametrizedTestFixtureForCompareOperators {};
class TestOperatorMore : public ParametrizedTestFixtureForCompareOperators {};
class TestOperatorEqual : public ParametrizedTestFixtureForCompareOperators {};
class TestOperatorLessOrEqual : public ParametrizedTestFixtureForCompareOperators {};

TEST_P(TestOperatorLess, less_test) {
    EXPECT_TRUE(num1_ < num2_);
}

TEST_P(TestOperatorMore, more_test) {
    EXPECT_TRUE(num1_ > num2_);
}

TEST_P(TestOperatorEqual, equal_test) {
    EXPECT_TRUE(num1_ == num2_);
}

TEST_P(TestOperatorLessOrEqual, less_or_equal_test) {
    EXPECT_TRUE(num1_ <= num2_);
}

INSTANTIATE_TEST_SUITE_P(
    BigIntTests,
    TestOperatorLess,
    ::testing::Values(
        std::make_tuple("170", "240"),
        std::make_tuple("-170", "-150"),
        std::make_tuple("-170", "240"),
        std::make_tuple("-145", "0")
    )
);

INSTANTIATE_TEST_SUITE_P(
    BigIntTests,
    TestOperatorMore,
    ::testing::Values(
        std::make_tuple("170", "95"),
        std::make_tuple("-170", "-250"),
        std::make_tuple("255", "240"),
        std::make_tuple("145", "0")
    )
);


INSTANTIATE_TEST_SUITE_P(
    BigIntTests,
    TestOperatorEqual,
    ::testing::Values(
        std::make_tuple("95", "95"),
        std::make_tuple("-170", "-170"),
        std::make_tuple("0", "0")
    )
);

INSTANTIATE_TEST_SUITE_P(
    BigIntTests,
    TestOperatorLessOrEqual,
    ::testing::Values(
        std::make_tuple("95", "95"),
        std::make_tuple("-170", "-170"),
        std::make_tuple("0", "0"),
        std::make_tuple("-95", "-0"),
        std::make_tuple("111", "189"),
        std::make_tuple("121", "122"),
        std::make_tuple("-100", "-60")
    )
);


