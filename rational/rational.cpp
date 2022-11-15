#include <rational.h>

#include <algorithm>
#include <utils.h>
#include <iostream>

namespace rational {
    rational::rational(std::string num) {
        if (num.front() == '-') {
            is_negative_ = true;
            num = num.substr(1);
        }

        size_t pos = num.find(".");
        std::string int_part = num.substr(0, pos);
        std::string float_part = num.substr(pos + 1);

        int_part_ = utils::make_vector_from_string(int_part);
        float_part_ = utils::make_vector_from_string(float_part);
    }

    rational::rational(const std::vector<int>& int_part, const std::vector<int>& float_part) :
        int_part_(int_part), float_part_(float_part) {}

    rational::rational(std::string int_part, std::string float_part) : 
        int_part_(int_part.size()), float_part_(float_part.size()) {
        if (int_part[0] == '-') {
            int_part = int_part.substr(1);
            is_negative_= true;
        }

        for (int64_t i = int_part.size() - 1; i >= 0; --i) {
            int_part_[int_part_.size() - i - 1] = int_part[i] - '0';
        }

        for (int64_t i = float_part.size() - 1; i >= 0; --i) {
            float_part_[float_part.size() - i - 1] = float_part[i] - '0';
        }
    }

    bool rational::is_negative() const {
        return is_negative_;
    }

    bool rational::operator==(const rational& other) const {
        return is_negative_ == other.is_negative_ && 
            int_part_ == other.int_part_ && float_part_ == other.float_part_;
    }

    bool rational::operator<=(const rational& other) const {
        return !(*this > other);
    }

    bool rational::operator>=(const rational& other) const {
        return !(*this < other);
    }

    bool rational::operator<(const rational& other) const {
        auto comp_greater = [](int a, int b){
            return a > b;
        };

        auto comp_less = [](int a, int b) {
            return a < b;
        };

        if (is_negative_ && !other.is_negative_) {
            return true;
        } else if (!is_negative_ && other.is_negative_) {
            return false;
        } else if (is_negative_ && other.is_negative_) {
            if (int_part_.size() > other.int_part_.size()) {
                return true;
            } else if (int_part_.size() < other.int_part_.size()) {
                return false;
            }

            if (utils::compare_two_positive_vectors(int_part_, other.int_part_, comp_greater)) {
                return true;
            } else if (utils::compare_two_positive_vectors(int_part_, other.int_part_, comp_less)) {
                return false;
            }

            if (utils::compare_two_positive_vectors(float_part_, other.float_part_, comp_greater)) {
                return true;
            }

            return false;
        }


        if (int_part_.size() > other.int_part_.size()) {
            return false;
        } else if (int_part_.size() < other.int_part_.size()) {
            return true;
        }

        if (utils::compare_two_positive_vectors(int_part_, other.int_part_, comp_greater)) {
            return false;
        } else if (utils::compare_two_positive_vectors(int_part_, other.int_part_, comp_less)) {
            return true;
        }

        if (utils::compare_two_positive_vectors(float_part_, other.float_part_, comp_greater)) {
            return false;
        }

        return true;
    }

    bool rational::operator>(const rational& other) const {
        return (!(*this < other) && !(*this == other));
    }

    rational operator+(const rational& lhs, const rational& rhs) {
        if (!lhs.is_negative_ && !rhs.is_negative_) {
            return sum_positive_nums(lhs, rhs);
        } else if (lhs.is_negative_ && rhs.is_negative_) {
            rational res = sum_positive_nums(lhs, rhs);
            res.is_negative_ = true;
            return res;
        } else if (lhs.is_negative_ && !rhs.is_negative_) {
            if (rhs > lhs) {
                return diff_positive_nums(rhs, lhs);
            }
            std::cout << "this if\n";
            rational res = diff_positive_nums(lhs, rhs);
            res.is_negative_ = true;
            return res;
        }

        if (lhs > rhs) {
            return diff_positive_nums(lhs, rhs);
        }

        rational res = diff_positive_nums(rhs, lhs);
        res.is_negative_ = true;
        return res;
    }

    rational operator-(const rational& lhs, const rational& rhs) {
        if (!lhs.is_negative_ && !rhs.is_negative_) {
            if (lhs > rhs) {
                return diff_positive_nums(lhs, rhs);
            }
            rational res = diff_positive_nums(rhs, lhs);
            res.is_negative_ = true;
            return res;
        } else if (lhs.is_negative_ && rhs.is_negative_) {
            if (rhs > lhs) {
                return diff_positive_nums(rhs, lhs);
            }

            rational res = diff_positive_nums(lhs, rhs);
            res.is_negative_ = true;
            return res;
        } else if (lhs.is_negative_ && !rhs.is_negative_) {
            rational res = sum_positive_nums(lhs, rhs);
            res.is_negative_ = true;
            return res;
        }

        return sum_positive_nums(lhs, rhs);
    }

    rational diff_positive_nums(const rational& lhs, const rational& rhs) {
        int carry = 0;
        std::vector<int> float_part_lhs = lhs.float_part_;
        std::vector<int> float_part_rhs = rhs.float_part_;
        std::vector<int> int_part_lhs = lhs.int_part_;
        std::vector<int> int_part_rhs = rhs.int_part_;

        if (float_part_lhs.size() > float_part_rhs.size()) {
            utils::add_trailing_zeros(float_part_rhs, float_part_lhs.size() - float_part_rhs.size());
        } else if (float_part_lhs.size() < float_part_rhs.size()) {
            utils::add_trailing_zeros(float_part_lhs, float_part_rhs.size() - float_part_lhs.size());
        }  

        std::vector<int> float_part_res;
        
        for (size_t i = 0; i < float_part_lhs.size(); ++i) {
            int cur_diff = float_part_lhs[i] - float_part_rhs[i] + carry;

            if (cur_diff < 0) {
                cur_diff += 10;
                carry = -1;
            } else {
                carry = 0;
            }

            float_part_res.push_back(cur_diff % BASE);
        }

        std::vector<int> int_part_res;

        for (size_t i = 0; i < std::min(int_part_lhs.size(), int_part_rhs.size()); ++i) {
            int cur_diff = int_part_lhs[i] - int_part_rhs[i] + carry;

            if (cur_diff < 0) {
                cur_diff += 10;
                carry = -1;
            } else {
                carry = 0;
            }

            int_part_res.push_back(cur_diff % BASE);
        }

        for (size_t i = std::min(int_part_lhs.size(), int_part_rhs.size()); 
            i < std::max(int_part_lhs.size(), int_part_rhs.size()); ++i) {
            if (int_part_lhs.size() > int_part_rhs.size()) {
                int cur_diff = int_part_lhs[i] + carry;
                if (cur_diff < 0) {
                    cur_diff += 10;
                    carry = -1;
                } else {
                    carry = 0;
                }
                int_part_res.push_back(cur_diff & BASE);
            } else {
                int cur_diff = int_part_rhs[i] + carry;
                if (cur_diff < 0) {
                    cur_diff += 10;
                    carry = -1;
                } else {
                    carry = 0;
                }
                int_part_res.push_back(cur_diff & BASE);
            }
        }
       
        return rational(int_part_res, float_part_res);
    }

    rational sum_positive_nums(const rational& lhs, const rational& rhs) {
        int carry = 0;
        std::vector<int> float_part_lhs = lhs.float_part_;
        std::vector<int> float_part_rhs = rhs.float_part_;
        std::vector<int> int_part_lhs = lhs.int_part_;
        std::vector<int> int_part_rhs = rhs.int_part_;

        if (float_part_lhs.size() > float_part_rhs.size()) {
            utils::add_trailing_zeros(float_part_rhs, float_part_lhs.size() - float_part_rhs.size());
        } else if (float_part_lhs.size() < float_part_rhs.size()) {
            utils::add_trailing_zeros(float_part_lhs, float_part_rhs.size() - float_part_lhs.size());
        }  
        
        std::vector<int> float_part_res;

        for (size_t i = 0; i < float_part_lhs.size(); ++i) {
            int cur_sum = float_part_lhs[i] + float_part_rhs[i] + carry;
            carry = cur_sum / BASE;
            float_part_res.push_back(cur_sum % BASE);
        }

        std::vector<int> int_part_res;

        for (size_t i = 0; i < std::min(int_part_lhs.size(), int_part_rhs.size()); ++i) {
            int cur_sum = int_part_lhs[i] + int_part_rhs[i] + carry;
            carry = cur_sum / BASE;
            int_part_res.push_back(cur_sum % BASE);
        }

        for (size_t i = std::min(int_part_lhs.size(), int_part_rhs.size()); 
            i < std::max(int_part_lhs.size(), int_part_rhs.size()); ++i) {
                if (int_part_lhs.size() > int_part_rhs.size()) {
                    int cur_sum = int_part_lhs[i] + carry;
                    carry = cur_sum / BASE;
                    int_part_res.push_back(cur_sum % BASE);
                } else {
                    int cur_sum = int_part_rhs[i] + carry;
                    carry = cur_sum / BASE;
                    int_part_res.push_back(cur_sum % BASE);
                }
            }

        if (carry) {
            int_part_res.push_back(carry);
         }

        return rational(int_part_res, float_part_res);
    }

    std::ostream& operator<<(std::ostream& os, const rational& r) {
        if (r.is_negative_) {
            os << "-";
        }   

        for (int64_t i = r.int_part_.size() - 1; i >= 0; --i) {
            os << r.int_part_[i];
        }

        os << ".";

        for (int64_t i = r.float_part_.size() - 1; i >= 0; --i) {
            os << r.float_part_[i];
        }   

        return os;
    }
} // namespace rational