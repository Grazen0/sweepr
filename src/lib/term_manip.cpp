#include "term_manip.h"
#include <iostream>

namespace term_manip {
    void clear_screen() {
        std::cout << CH_CLEAR << CH_CURSOR_RESET;
    }
}
