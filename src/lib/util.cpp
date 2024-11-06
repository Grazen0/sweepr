#include "util.h"
#include <iostream>
#include <istream>

namespace sweepr::util {
    int rand_range(const int min, const int max) {
        return min + std::rand() % (max - min + 1);
    }

    // https://stackoverflow.com/questions/21032491/cin-get-isnt-working-as-it-should
    void wait_for_enter() {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    char to_lowercase(const char ch) {
        if ('A' <= ch && ch <= 'Z')
            return ch - 'A' + 'a';

        return ch;
    }
}
