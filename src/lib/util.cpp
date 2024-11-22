#include "util.h"

namespace util {
    int rand_range(const int min, const int max) {
        return min + std::rand() % (max - min + 1);
    }

    char to_lowercase(const char ch) {
        if ('A' <= ch && ch <= 'Z')
            return ch - 'A' + 'a';

        return ch;
    }
}
