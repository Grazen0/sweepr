#ifndef LIB_UTIL
#define LIB_UTIL

#include <vector>

namespace sweepr::util {
    void clear_screen();

    int rand_range(const int min, const int max);

    void shuffle_first_n(std::vector<std::pair<int, int>> &vec, const int n);

    void wait_for_enter();

    char to_lowercase(const char ch);
}

#endif
