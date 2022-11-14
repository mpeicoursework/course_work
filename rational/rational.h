#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace rational {

    class rational {
    public:
        rational(std::string int_part, std::string float_part);
        rational(float float_num);
        rational(double double_num);
        rational(long double long_double_num);

        rational operator+(const rational& other);
        rational operator-(const rational& other);
        rational operator*(const rational& other);
        rational operator/(const rational& other);

        bool operator==(const rational& other);
        bool operator<=(const rational& other);
        bool operator>=(const rational& other);
        bool operator<(const rational& other);
        bool operator>(const rational& other);

        bool is_negative() const;
        
        std::string get_string_view_num() const;
    private:
        bool is_negative_ = false;
        std::vector<int> int_part_;
        std::vector<int> float_part_;
    };

    std::ostream& operator<<(std::ostream& os, const rational& r);
} // namespace rational