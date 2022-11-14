#include <vector>
#include <string>

namespace utils {

    std::vector<int> make_vector_from_string(const std::string& s);
    void remove_leading_zeros(std::vector<int>& v);
    void add_trailing_zeros(std::vector<int>& v, int count_zeros);

} // namespace utils