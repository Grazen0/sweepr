#include "util.h"
#include <iostream>
#include <limits>
#include <vector>

namespace sweepr::util {
    void clear_screen() {
        // https://stackoverflow.com/questions/17335816/clear-screen-using-c
        std::cout << "\033[2J\033[1;1H";
    }

    int rand_range(const int min, const int max) {
        return min + std::rand() % (max - min + 1);
    }

    // https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
    void shuffle_first_n(std::vector<std::pair<int, int>>& vec, const int n) {
        for (int i = 0; i < n; i++) {
            const int swap_target = rand_range(i, vec.size() - 1);

            if (swap_target != i) {
                const auto tmp = vec[i];
                vec[i] = vec[swap_target];
                vec[swap_target] = tmp;
            }
        }
    }

    void wait_for_enter() {
        // Vaciar el buffer de cin
        // https://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // Procesar hasta un '\n'
        std::cin.ignore();
    }

    char to_lowercase(const char ch) {
        if ('A' <= ch && ch <= 'Z')
            return ch - 'A' + 'a';

        return ch;
    }
}
