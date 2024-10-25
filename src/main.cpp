#include <iostream>
#include "lib/term_manip.h"

int main() {
    term_manip::clear_screen();

    std::cout << term_manip::color::BLUE << term_manip::color::BOLD;
    std::cout << "Hello, world!" << std::endl;
    std::cout << term_manip::color::RESET;

    return 0;
}
