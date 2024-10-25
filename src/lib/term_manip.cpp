#include "term_manip.h"
#include <iostream>

void term_manip::clear_screen() {
    std::cout << CLEAR_SCREEN << CURSOR_RESET;
}
