#include <rational.h>

#include <algorithm>
#include <utils.h>
#include <iostream>

namespace rational {

    rational::rational(long long numerator_, long long denominator_) :
        numerator(numerator_), denominator(denominator_) {
            this->normalized();
        }

    bool rational::operator==(const rational& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool rational::operator<=(const rational& other) const {
        return !(*this > other);
    }

    bool rational::operator>=(const rational& other) const {
        return !(*this < other);
    }

    bool rational::operator<(const rational& other) const {
        long long lcm = utils::lcm(denominator, other.denominator);
        return (numerator * (lcm / denominator)) < (other.numerator * (lcm / other.denominator));
    }

    bool rational::operator>(const rational& other) const {
        return (!(*this < other) && !(*this == other));
    }

    rational operator-(const rational& r) {
        return rational(-r.numerator, r.denominator);
    }

    rational operator+(const rational& lhs, const rational& rhs) {
        long long lcm = utils::lcm(lhs.denominator, rhs.denominator);
        auto coef = [&](const rational& r) {
            return lcm / r.denominator;
        };
        long long numerator = lhs.numerator * coef(lhs) + rhs.numerator * coef(rhs);
        return rational(numerator, lcm).normalized();
    }

    rational operator-(const rational& lhs, const rational& rhs) {
        return lhs + (-rhs);
    }

    rational operator*(const rational& lhs, const rational& rhs) {
        return rational(lhs.numerator * rhs.numerator, lhs.denominator * rhs.denominator).normalized();
    }

    rational operator/(const rational& lhs, const rational& rhs) {
        return rational(lhs.numerator * rhs.denominator, lhs.denominator * rhs.numerator).normalized();
    }

    std::ostream& operator<<(std::ostream& os, const rational& r) {
        if (r.denominator ==  1) {
            os << r.numerator;
        } else {
            os << r.numerator << " / " << r.denominator;
        }
        return os;
    }

    rational rational::normalized() {
        long long gcd = utils::gcd(numerator, denominator);
        numerator /= gcd; denominator /= gcd;
        return *this;
    }

} // namespace rational