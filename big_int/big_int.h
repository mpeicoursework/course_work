#pragma once

#include <iostream>
#include <vector>

#include <utils.h>

constexpr int BASE = 10;

namespace big_int 
{

class big_int {
public:
    big_int()=default;
    big_int(std::string s);
    big_int(const std::vector<int>& num) : num_(num) {};
    big_int(const big_int& other);

    friend std::ostream& operator<<(std::ostream& os, const big_int& bi);

    friend big_int operator+(const big_int& lhs, const big_int& rhs);
    friend big_int operator-(const big_int& lhs, const big_int& rhs);
    friend big_int operator*(const big_int& lhs, const big_int& rhs);
    friend big_int operator/(const big_int& lhs, const big_int& rhs);
    friend big_int operator%(const big_int& lhs, const big_int& rhs);

    friend big_int sum_positive_nums(const big_int& lhs, const big_int& rhs);
    friend big_int diff_positive_nums(const big_int& lhs, const big_int& rhs);
    friend big_int multiply_positive_nums(const big_int& lhs, const big_int& rhs);
    friend big_int divide_positive_nums(const big_int& lhs, const big_int& rhs);

    bool operator==(const big_int& other) const;
    bool operator!=(const big_int& other) const;
    bool operator<=(const big_int& other) const;
    bool operator>=(const big_int& other) const;
    bool operator<(const big_int& other) const;
    bool operator>(const big_int& other) const;

    big_int& operator=(const big_int& other);

    big_int abs() const;

    bool is_signed() const;
private:
    bool is_signed_ = false;
    std::vector<int> num_;
};

big_int gcd(const big_int& lhs, const big_int& rhs);
big_int lcm(const big_int& lhs, const big_int& rhs);

} // namespace big_int