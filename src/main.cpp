#include <iostream>
#include "lib/term_manip.h"

int main() {
    term_manip::clear_screen();
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
