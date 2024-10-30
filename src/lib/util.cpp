#include "util.h"
#include <cstdlib>
#include <iostream>
#include <vector>

void sweepr::util::clear_screen() {
    // https://stackoverflow.com/questions/17335816/clear-screen-using-c
    std::cout << "\033[2J\033[1;1H";
}

int sweepr::util::rand_range(const int min, const int max) {
    return min + std::rand() % (max - min + 1);
}

// https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
void sweepr::util::shuffle_first_n(std::vector<int>& vec, const int n) {
    for (int i = 0; i < n; i++) {
        const int swap_target = rand_range(i, vec.size() - 1);

        if (swap_target != i) {
            const int tmp = vec[i];
            vec[i] = vec[swap_target];
            vec[swap_target] = tmp;
        }
    }
}
