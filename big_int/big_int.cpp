#include <big_int.h>

#include <algorithm>

namespace big_int
{
big_int::big_int(std::string s) {
    if (std::count(s.begin(), s.end(), '0') == s.size()) {
        s = "0";
    }

    if (s[0] == '-') {
        is_signed_ = true;
        s = s.substr(1);
    }

    num_.reserve(s.size());

    for (int i = s.size() - 1; i >= 0; --i) {
        num_.push_back(static_cast<int>(s[i] - '0'));
    }
}

big_int::big_int(const big_int& other) {
    num_ = other.num_;
    is_signed_ = other.is_signed_;
}

bool big_int::operator==(const big_int& other) const {
    return is_signed_ == other.is_signed_ && num_ == other.num_;
}

bool big_int::operator!=(const big_int& other) const {
    return !(*this == other);
}

bool big_int::operator<(const big_int& other) const {
    if (is_signed_ && !other.is_signed_) {
        return true;
    }

    if (is_signed_ && other.is_signed_) {
        if (num_.size() > other.num_.size()) {
            return true;
        } else if (num_.size() < other.num_.size()) {
            return false;
        }

        for (int i = num_.size() - 1; i >= 0; --i) {
            if (num_[i] > other.num_[i]) {
                return true;
            } else if (num_[i] < other.num_[i]) {
                return false;
            }
        }

        return false;
    }

    if (num_.size() > other.num_.size()) {
        return false;
    } else if (num_.size() < other.num_.size()) {
        return true;
    }

    for (int i = num_.size() - 1; i >= 0; --i) {
        if (num_[i] > other.num_[i]) {
            return false;
        } else if (num_[i] < other.num_[i]) {
            return true;
        }
    }

    return false;
}

bool big_int::operator<=(const big_int& other) const {
    return (*this < other) || (*this == other);
}

bool big_int::operator>(const big_int& other) const {
    return !(*this <= other);
}

bool big_int::operator>=(const big_int& other) const {
    return !(*this < other);
}


big_int operator+(const big_int& lhs, const big_int& rhs) {
    if (!lhs.is_signed_ && !rhs.is_signed_) {
        return sum_positive_nums(lhs, rhs);
    }

    if (lhs.is_signed_ && rhs.is_signed_) {
        big_int res = sum_positive_nums(lhs, rhs);
        res.is_signed_ = true;
        return res;
    }

    if (!lhs.is_signed_ && rhs.is_signed_) {
        if (lhs.abs() > rhs.abs()) {
            return diff_positive_nums(lhs, rhs.abs());
        }

        big_int res = diff_positive_nums(rhs.abs(), lhs);
        res.is_signed_ = true;
        return res;
    }

    if (lhs.abs() > rhs.abs()) {
        big_int res = diff_positive_nums(lhs.abs(), rhs.abs());
        res.is_signed_ = true;
        return res;
    }  

    return diff_positive_nums(rhs, lhs.abs());
}

big_int operator-(const big_int& lhs, const big_int& rhs) {
    if (!lhs.is_signed_ && !rhs.is_signed_) {
        if (lhs > rhs) {
            return diff_positive_nums(lhs, rhs);
        }

        big_int res = diff_positive_nums(rhs, lhs);
        res.is_signed_ = true;
        return res;
    }

    if (lhs.is_signed_ && rhs.is_signed_) {
        if (lhs.abs() < rhs.abs()) {
            return diff_positive_nums(rhs.abs(), lhs.abs());
        }

        big_int res = diff_positive_nums(lhs.abs(), rhs.abs());
        res.is_signed_ = true;
        return res;
    }

    if (!lhs.is_signed_ && rhs.is_signed_) {
        return sum_positive_nums(lhs, rhs.abs());
    }

    big_int res = sum_positive_nums(lhs.abs(), rhs.abs());
    res.is_signed_ = true;
    return res;
}

big_int operator*(const big_int& lhs, const big_int& rhs) {
    big_int res = multiply_positive_nums(lhs.abs(), rhs.abs());
    res.is_signed_ = lhs.is_signed_ ^ rhs.is_signed_;
    return res;
}

big_int operator/(const big_int& lhs, const big_int& rhs) {
    big_int res = divide_positive_nums(lhs.abs(), rhs.abs());
    res.is_signed_ = lhs.is_signed_ ^ rhs.is_signed_;
    return res;
}   

big_int operator%(const big_int& lhs, const big_int& rhs) {
    big_int division = lhs / rhs;
    return lhs - (rhs * division);
}

big_int sum_positive_nums(const big_int& lhs, const big_int& rhs) {
    std::vector<int> num;
    int carry = 0;
    for (size_t i = 0; i < std::min(lhs.num_.size(), rhs.num_.size()); ++i) {
        int cur_sum = lhs.num_[i] + rhs.num_[i] + carry;
        carry = cur_sum / BASE;
        num.push_back(cur_sum % BASE);
    }

    for (size_t i = std::min(lhs.num_.size(), rhs.num_.size()); 
        i < std::max(lhs.num_.size(), rhs.num_.size()); ++i) {
        if (lhs.num_.size() > rhs.num_.size()) {
            int cur_sum = lhs.num_[i] + carry;
            carry = cur_sum / BASE;
            num.push_back(cur_sum % BASE);
        } else {
            int cur_sum = rhs.num_[i] + carry;
            carry = cur_sum / BASE;
            num.push_back(cur_sum % BASE);
        }
    }

    if (carry != 0) {
        num.push_back(carry);  
    }

    return big_int(num);
}

big_int diff_positive_nums(const big_int& lhs, const big_int& rhs) {
    if (lhs == rhs) {
        return big_int("0");
    }
    std::vector<int> num;
    int carry = 0;
    for (size_t i = 0; i < std::min(lhs.num_.size(), rhs.num_.size()); ++i) {
        int cur_diff = lhs.num_[i] - rhs.num_[i] + carry;
        if (cur_diff < 0) {
            cur_diff += 10;
            carry = -1;
        } else {
            carry = 0;
        }

        num.push_back(cur_diff % BASE);
    }
    
    for (size_t i = std::min(lhs.num_.size(), rhs.num_.size()); 
        i < std::max(lhs.num_.size(), rhs.num_.size()); ++i) {
        if (lhs.num_.size() > rhs.num_.size()) {
            int cur_diff = lhs.num_[i] + carry;
            if (cur_diff < 0) {
                cur_diff += 10;
                carry = -1;
            } else {
                carry = 0;
            }
            num.push_back(cur_diff % BASE);
         } else {
            int cur_diff = rhs.num_[i] + carry;
            if (cur_diff < 0) {
                cur_diff += 10;
                carry = -1;
            } else {
                carry = 0;
            }
             num.push_back(cur_diff & BASE);
        }
    }

    utils::remove_leading_zeros(num);

    return big_int(num); 
}

big_int multiply_positive_nums(const big_int& lhs, const big_int& rhs) {
    std::vector<int> res(lhs.num_.size() + rhs.num_.size(), 0);
    for (size_t i = 0; i < rhs.num_.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < lhs.num_.size(); ++j) {
            res[i + j] += carry + lhs.num_[j] * rhs.num_[i];
            carry = res[i + j] / BASE;
            res[i + j] %= BASE;
        }
        res[i + lhs.num_.size()] += carry;
    }

    utils::remove_leading_zeros(res);
    return big_int(res);
}

big_int divide_positive_nums(const big_int& lhs, const big_int& rhs) {
    if (lhs < rhs) {
        return big_int(std::vector<int>{0});
    }

    // TODO: maybe found more effective algorithm for division
    big_int res(std::vector<int>(lhs.num_.size() - rhs.num_.size() + 1, 0));

    for (int64_t i = res.num_.size() - 1; i >= 0; --i) {
        while (multiply_positive_nums(res, rhs) <= lhs) {
            ++res.num_[i];
        }
        --res.num_[i];
    }

    utils::remove_leading_zeros(res.num_);

    return res;   
}

big_int& big_int::operator=(const big_int& other) {
    if (this == &other) {
        return *this;
    }

    num_ = other.num_;
    is_signed_ = other.is_signed_;
    return *this;
}

big_int big_int::abs() const {
    return big_int(num_);
}

big_int gcd(const big_int& lhs, const big_int& rhs) {
    big_int a = lhs;
    big_int b = rhs;
    while (a != b) {
        if (a > b) {
            a = a - b;
        } else {
            b = b - a;
        }
    }
    return a;
}

big_int lcm(const big_int& lhs, const big_int& rhs) {
    return (lhs * rhs) / gcd(lhs, rhs);
}

std::ostream& operator<<(std::ostream& os, const big_int& bi) {
    if (bi.is_signed_) {
        os << "-";
    }

    for (int i = bi.num_.size() - 1; i >= 0; --i) {
        os << bi.num_[i];
    }

    return os;
}

bool big_int::is_signed() const {
    return is_signed_;
}

} // namespace big_int