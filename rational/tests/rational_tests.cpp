#include <gtest/gtest.h>

#include <rational.h>
#include <iostream>

TEST(rational_tests, equality_operator_test) {
    rational::rational r1(1,3);
    rational::rational r2(1,4);
    ASSERT_TRUE(r2 < r1);
    ASSERT_TRUE(r1 > r2);
    
    rational::rational r3(1,3);
    ASSERT_TRUE(r1 == r3);
    ASSERT_TRUE(r1 >= r3);

    rational::rational r4(-5,11);
    rational::rational r5(-17, 10);
    ASSERT_TRUE(r5 < r4);
}

TEST(rational_tests, adding_operator_test) {
    rational::rational r1(1,6);
    rational::rational r2(2,6);
    rational::rational r3 = r1 + r2;
    rational::rational expected1(1,2);
    ASSERT_EQ(r3, expected1);

    rational::rational r4(1,3);
    rational::rational r5(1,2);
    rational::rational r6 = r4 + r5;
    rational::rational expected2(5,6);
    ASSERT_EQ(r6, expected2);

    rational::rational r7(-1,2);
    rational::rational r8(-1,2);
    rational::rational r9 = r7 + r8;
    rational::rational expected3(-1,1);
    ASSERT_EQ(r9, expected3);
}

TEST(rational_tests, diff_operator_tests) {
    rational::rational r10(2,1);
    rational::rational r11(1,2);
    rational::rational r12 = r10 - r11;
    rational::rational expected4(3,2);
    ASSERT_EQ(r12, expected4);

    rational::rational r13(-3,2);
    rational::rational r14(1,2);
    rational::rational r15 = r13 - r14;
    rational::rational expected5(-2,1);
    ASSERT_EQ(r15, expected5);
}

