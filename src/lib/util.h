#ifndef LIB_UTIL
#define LIB_UTIL

#include <iostream>
#include <limits>
#include <utility>
#include <vector>

namespace util {
    // Cuando se usan templates, la definición de la cosa en cuestión debe estar
    // en el mismo header
    // https://www.geeksforgeeks.org/how-to-handle-wrong-data-type-input-in-cpp/
    template <typename T>
    T safe_prompt() {
        T x;
        std::cin >> x;

        while (std::cin.fail()) {
            std::cin.clear(); // Resetea el estado del cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Vacia el buffer
            std::cin >> x;
        }

        return x;
    }

    int rand_range(const int min, const int max);

    // https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
    template <typename T>
    void partial_shuffle(std::vector<T>& vec, const int n) {
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
