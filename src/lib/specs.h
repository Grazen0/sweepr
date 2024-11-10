#ifndef LIB_SPECS
#define LIB_SPECS

namespace sweepr::specs {
    namespace Difficulty {
        enum Difficulty { Easy, Medium, Hard };
    }

    int get_board_size(const Difficulty::Difficulty difficulty);

    int generate_mine_count(const Difficulty::Difficulty difficulty);
}

#endif
