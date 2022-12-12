#include <rational.h>

#include <algorithm>
#include <utility>
#include <utils.h>
#include <iostream>
#include <string>
#include <math.h>

namespace rational {
rational::rational(const std::string& s) {
    // TODO: incorrect string maybe need checking
    std::string fraction = s;
    if (fraction[0] == '-') {
        fraction = fraction.substr(1);
        is_signed_ = true;
    }

    std::string numerator = s.substr(0, s.find('/'));
    std::string denominator = s.substr(s.find('/') + 1);
    numerator_ = big_int::big_int(numerator);
    denominator_ = big_int::big_int(denominator);
    normalized();
}

rational::rational(const std::string& numerator, const std::string& denominator) {
    numerator_ = big_int::big_int(numerator);
    denominator_ = big_int::big_int(denominator);
}

rational::rational(const big_int::big_int& numerator, const big_int::big_int& denominator) :
    numerator_(numerator), denominator_(denominator) {
    is_signed_ = numerator_.is_signed() ^ denominator_.is_signed();        
}

rational::rational(long long numerator, long long denominator) :
    numerator_(std::to_string(numerator)), denominator_(std::to_string(denominator)) {
        normalized();
    }

rational::rational(const rational& other) : numerator_(other.numerator_),
    denominator_(other.denominator_), is_signed_(other.is_signed_) {}

rational::rational(float number) {
    rational((long double)number);
}

rational::rational(double number) {
    rational((long double)number);
}

rational::rational(long double number_) {
    std::string number = std::to_string(number_);
    int dot_index = number.find(".");
    int approximation = 6;
    std::string approx_number = number.substr(0, dot_index + approximation);
    long long denominator = pow(10, approximation);
    long long numerator = std::stoi(approx_number) * denominator;
    rational(numerator, denominator);
}

bool rational::operator==(const rational& other) const {
    return numerator_ == other.numerator_ && denominator_ == other.denominator_;
}

bool rational::operator<=(const rational& other) const {
    return !(*this > other);
}

bool rational::operator>=(const rational& other) const {
    return !(*this < other);
}

bool rational::operator<(const rational& other) const {
    big_int::big_int lcm = big_int::lcm(denominator_, other.denominator_);
    return (numerator_ * (lcm / denominator_)) < (other.numerator_ * (lcm / other.denominator_));
}

bool rational::operator>(const rational& other) const {
    return (!(*this < other) && !(*this == other));
}

bool rational::operator!=(const rational& other) const {
    return !(*this == other);
}

rational rational::operator+=(const rational& other) {
    return *this = *this + other;
}
    
rational rational::operator-=(const rational& other) {
    return *this = *this - other;
}
    
rational rational::operator*=(const rational& other) {
    return *this = *this * other;
}

rational rational::operator/=(const rational& other) {
    return *this = *this / other;
}

rational operator+(const rational& lhs, const rational& rhs) {
    big_int::big_int lcm = big_int::lcm(lhs.denominator_, rhs.denominator_);
    auto coef = [&](const rational& r) {
        return lcm / r.denominator_;
    };
    big_int::big_int numerator = lhs.numerator_ * coef(lhs) + rhs.numerator_ * coef(rhs);
    return rational(numerator, lcm).normalized();
} 

rational operator-(const rational& lhs, const rational& rhs) {
    big_int::big_int lcm = big_int::lcm(lhs.denominator_, rhs.denominator_);
    auto coef = [&](const rational& r) {
        return lcm / r.denominator_;
    };
    big_int::big_int numerator = lhs.numerator_ * coef(lhs) - rhs.numerator_ * coef(rhs);
    return rational(numerator, lcm).normalized();
}

rational operator*(const rational& lhs, const rational& rhs) {
    return rational(lhs.numerator_ * rhs.numerator_, lhs.denominator_ * rhs.denominator_).normalized();
}

rational operator/(const rational& lhs, const rational& rhs) {
    return rational(lhs.numerator_ * rhs.denominator_, lhs.denominator_ * rhs.numerator_).normalized();
}

rational operator+(const rational& lhs, long long rhs) {
    return lhs + rational(rhs, 1);
}

rational operator-(const rational& lhs, long long rhs) {
    return lhs - rational(rhs, 1);
}

rational operator-(const rational& r) {
    auto res = r;
    res.is_signed_ = true;
    return res;
}

rational operator*(const rational& lhs, long long rhs) {
    return lhs * rational(rhs, 1);
}

rational operator/(const rational& lhs, long long rhs) {
    return lhs / rational(rhs, 1);
}

bool rational::is_negative() const {
    return is_signed_;
}

std::ostream& operator<<(std::ostream& os, const rational& r) {
    if (r.denominator_ ==  big_int::big_int("1")) {
        os << r.numerator_;
    } else {
        os << r.numerator_ << " / " << r.denominator_;
    }
    return os;
}


rational abs(const rational& number) {
    return number.is_negative() ? -number : number;
}

rational rational::normalized() {
    big_int::big_int gcd = big_int::gcd(numerator_, denominator_);
    numerator_ = numerator_ / gcd;
    denominator_ = denominator_ / gcd;
    return *this;
}

// TODO: the following three methods contains duplicate code, neeeded remove him

float rational::get_float() const {
    // TODO: exception needed to be throw
    return static_cast<float>(numerator_.get_int()) / static_cast<float>(denominator_.get_int());
}

double rational::get_double() const {
    // TODO: exception needed to be throw
    return static_cast<double>(numerator_.get_long()) / static_cast<double>(denominator_.get_long());
}

long double rational::get_long_double() const {
    // TODO: exception needed to be throw
    return static_cast<double>(numerator_.get_long()) / static_cast<double>(denominator_.get_long());
}

} // namespace rationalg