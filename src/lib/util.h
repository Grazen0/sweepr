#ifndef LIB_UTIL
#define LIB_UTIL

namespace sweepr::util {
    void clear_screen();

    int rand_range(const int min, const int max);

    void shuffle_first_n(int* arr, const int arr_len, const int n);

    char to_lowercase(const char ch);
}

#endif
