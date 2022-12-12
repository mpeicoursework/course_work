#include <utils.h>

namespace utils {

    std::vector<int> make_vector_from_string(const std::string& s) {
        std::vector<int> res(s.size());
        for (int64_t i = s.size() - 1; i >= 0; --i) {
            res[res.size() - i - 1] = s[i] - '0';
        }
        return res;
    }

    void remove_leading_zeros(std::vector<int>& v) {
        while (v.size() > 0 && v.back() == 0) {
            v.pop_back();
        }
    }

    std::string make_string_from_vector(const std::vector<int>& v) {
        std::string s;
        s.reserve(v.size());
        for (int64_t i = v.size() - 1; i >= 0; --i) {
            s.push_back(v[i] + '0');
        }
        return s;
    } 

    void add_trailing_zeros(std::vector<int>& v, int count_zeros) {
        // TODO: maybe using deque here for optimization
        for (int i = 0; i < count_zeros; ++i) {
            v.insert(v.begin(), 0);
        }
    }

}