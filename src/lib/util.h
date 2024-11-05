#ifndef LIB_UTIL
#define LIB_UTIL

#include <iostream>
#include <limits>
#include <utility>
#include <vector>

namespace sweepr::util {
    void clear_screen();

    // https://www.geeksforgeeks.org/how-to-handle-wrong-data-type-input-in-cpp/
    template <typename T>
    T safe_prompt() {
        T x;
        std::cin >> x;

        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> x;
        }

        return x;
    }

    int rand_range(const int min, const int max);

    // Cuando se usan templates, la definición de la cosa en cuestión debe estar
    // en el mismo header
    // https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
    template <typename T>
    void shuffle_first_n(std::vector<T> &vec, const int n) {
        for (int i = 0; i < n; i++) {
            const int swap_target = rand_range(i, vec.size() - 1);

            if (swap_target != i) {
                std::swap(vec[i], vec[swap_target]);
            }
        }
    }

    void wait_for_enter();

    char to_lowercase(const char ch);
}

#endif
