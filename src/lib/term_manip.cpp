#include "term_manip.h"
#include <iostream>

void term_manip::clear_screen() {
    std::cout << CH_CLEAR << CH_CURSOR_RESET;
}
