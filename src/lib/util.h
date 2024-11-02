#ifndef LIB_UTIL
#define LIB_UTIL

#include <vector>
namespace sweepr::util {
    void clear_screen();

    int rand_range(const int min, const int max);

    void shuffle_first_n(std::vector<int>& vec, const int n);

    char to_lowercase(const char ch);
}

#endif
