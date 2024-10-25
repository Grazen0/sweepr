#include <iostream>
#include "lib/term_manip.h"

int main() {
    term_manip::clear_screen();

    std::cout << term_manip::BLUE << term_manip::BOLD;
    std::cout << "Hello, world!" << std::endl;
    std::cout << term_manip::RESET;

    return 0;
}
