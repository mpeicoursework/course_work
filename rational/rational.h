#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace rational {

    class rational {
    public:
        rational() = default;
        rational(const std::vector<int>& int_part, const std::vector<int>& float_part);
        rational(std::string num);
        rational(std::string int_part, std::string float_part);
        rational(float float_num);
        rational(double double_num);
        rational(long double long_double_num);

        friend rational operator+(const rational& lhs, const rational& rhs);
        friend rational operator-(const rational& lhs, const rational& rhs);
        friend rational operator*(const rational& lhs, const rational& rhs);
        friend rational operator/(const rational& lhs, const rational& rhs);

        friend std::ostream& operator<<(std::ostream& os, const rational& r);

        friend rational sum_positive_nums(const rational& lhs, const rational& rhs);
        friend rational diff_positive_nums(const rational& lhs, const rational& rhs);

        bool operator==(const rational& other) const;
        bool operator<=(const rational& other) const;
        bool operator>=(const rational& other) const;
        bool operator<(const rational& other) const;
        bool operator>(const rational& other) const;

        bool is_negative() const;
        
    private:
        const int BASE = 10; // constexpr?
        bool is_negative_ = false;
        std::vector<int> int_part_;
        std::vector<int> float_part_;
    };
} // namespace rational