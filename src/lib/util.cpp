#include "util.h"
#include <iostream>

void sweepr::util::clear_screen() {
    // https://stackoverflow.com/questions/17335816/clear-screen-using-c
    std::cout << "\033[2J\033[1;1H";
}
