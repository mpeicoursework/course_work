#pragma once

#include <iostream>
#include <vector>
#include <string>

constexpr int BASE = 10;

namespace rational {

    class rational {
    public:
        rational() = default;
        rational(long long numerator_, long long denominator_);
        rational(float float_num);
        rational(double double_num);
        rational(long double long_double_num);

        friend rational operator-(const rational& r);
        friend rational operator+(const rational& lhs, const rational& rhs);
        friend rational operator-(const rational& lhs, const rational& rhs);
        friend rational operator*(const rational& lhs, const rational& rhs);
        friend rational operator/(const rational& lhs, const rational& rhs);

        friend std::ostream& operator<<(std::ostream& os, const rational& r);

        bool operator==(const rational& other) const;
        bool operator<=(const rational& other) const;
        bool operator>=(const rational& other) const;
        bool operator<(const rational& other) const;
        bool operator>(const rational& other) const;

    private:
        long long numerator, denominator;

        rational normalized();

    };

} // namespace rational