#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <big_int.h>

namespace rational {

class rational {
public:
    rational() = default;
    rational(const std::string& s);
    rational(const std::string& numerator, const std::string& denominator);
    rational(const big_int::big_int& numerator, const big_int::big_int& denominator);

    friend rational operator+(const rational& lhs, const rational& rhs);
    friend rational operator-(const rational& lhs, const rational& rhs);
    friend rational operator*(const rational& lhs, const rational& rhs);
    friend rational operator/(const rational& lhs, const rational& rhs);

    friend rational operator-(const rational& r);

    friend std::ostream& operator<<(std::ostream& os, const rational& r);

    friend rational sum_positive_nums(const rational& lhs, const rational& rhs);
    friend rational diff_positive_nums(const rational& lhs, const rational& rhs);

    friend bool operator==(const rational& lhs, const rational& rhs);
    bool operator<=(const rational& other) const;
    bool operator>=(const rational& other) const;
    bool operator<(const rational& other) const;
    bool operator>(const rational& other) const;

    bool is_negative() const;
private:
    rational normalized();

    bool is_signed_ = false;
    big_int::big_int numerator_;
    big_int::big_int denominator_;
};
} // namespace rational