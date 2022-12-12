#pragma once

#include <vector>
#include <string>

namespace utils {

    std::vector<int> make_vector_from_string(const std::string& s);

    std::string make_string_from_vector(const std::vector<int>& v);

    void remove_leading_zeros(std::vector<int>& v);

    void add_trailing_zeros(std::vector<int>& v, int count_zeros);

    template<typename Comparator>
    bool compare_two_positive_vectors(const std::vector<int>& v1, const std::vector<int>& v2, Comparator comp) {
        for (int64_t i = v1.size(); i >= 0; --i) {
            if (comp(v1[i], v2[i])) {
                return true;
            }
        }
        
        return false;
    }

} // namespace utils