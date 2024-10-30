#include "util.h"
#include <cstdlib>
#include <iostream>

void sweepr::util::clear_screen() {
    // https://stackoverflow.com/questions/17335816/clear-screen-using-c
    std::cout << "\033[2J\033[1;1H";
}

int sweepr::util::rand_range(const int min, const int max) {
    return min + std::rand() % (max - min + 1);
}

// https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
void sweepr::util::shuffle_first_n(int* arr, const int arr_len, const int n) {
    for (int i = 0; i < n; i++) {
        const int swap_target = rand_range(i, arr_len - 1);

        if (swap_target != i) {
            const int tmp = arr[i];
            arr[i] = arr[swap_target];
            arr[swap_target] = tmp;
        }
    }
}

char sweepr::util::to_lowercase(const char ch) {
    if ('A' <= ch && ch <= 'Z')
        return ch - 'A' + 'a';

    return ch;
}
