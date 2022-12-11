#include <gtest/gtest.h>

#include <rational.h>
#include <iostream>

TEST(rational_tests, equality_operator_test) {
    std::cout << "run test\n";
    rational::rational r1("25.49");
    rational::rational r2("14.492");
    std::cout << r1 << std::endl;
    ASSERT_TRUE(r2 < r1);
    ASSERT_TRUE(r1 > r2);
    
    rational::rational r3("25.49");
    ASSERT_TRUE(r1 == r3);
    ASSERT_TRUE(r1 >= r3);

    rational::rational r4("-25.10314");
    rational::rational r5("-50.21");
    ASSERT_TRUE(r5 < r4);
}

// TEST(rational_tests, adding_operator_test) {
//     rational::rational r1("25.49");
//     rational::rational r2("14.492");
//     rational::rational r3 = r1 + r2;
//     rational::rational expected1("39.982");
//     ASSERT_EQ(r3, expected1);

//     rational::rational r4("0.52");
//     rational::rational r5("0.79");
//     rational::rational r6 = r4 + r5;
//     rational::rational expected2("1.31");
//     ASSERT_EQ(r6, expected2);

//     rational::rational r7("-0.52");
//     rational::rational r8("-1.52");
//     rational::rational r9 = r7 + r8;
//     rational::rational expected3("-2.04");
//     ASSERT_EQ(r9, expected3);

//     // rational::rational r10("-0.52");
//     // rational::rational r11("1.52");
//     // rational::rational r12 = r10 + r11;
//     // rational::rational expected4("1.00");
//     // ASSERT_EQ(r12, expected4);

//     // rational::rational r13("-1.52");
//     // rational::rational r14("0.49");
//     // rational::rational r15 = r13 + r14;
//     // std::cout << r15 << std::endl;
//     // rational::rational expected5("-1.03");
//     // ASSERT_EQ(r15, expected5);
// }

// TEST(rational_tests, diff_operator_tests) {
//     rational::rational r1("25.49");
//     rational::rational r2("14.492");
//     rational::rational r3 = r1 - r2;
//     rational::rational expected("10.998");
//     ASSERT_EQ(r3, expected);
// }

