#include <rational.h>

namespace rational {
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

    std::string rational::get_string_view_num() const {
        
    }

    std::ostream& operator<<(std::ostream& os, const rational& r) {
        if (r.is_negative()) {
            os << "-";
        }



        return os;
        //for (int64_t i = r.int_part_.size() - 1; i )
    }
} // namespace rational