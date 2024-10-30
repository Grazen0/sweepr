#ifndef LIB_SPECS
#define LIB_SPECS

namespace sweepr::specs {
    constexpr int DIFFICULTY_EASY = 1;
    constexpr int DIFFICULTY_MEDIUM = 2;
    constexpr int DIFFICULTY_HARD = 3;

    int get_board_size(const int difficulty);

    int generate_mine_count(const int difficulty);
}

#endif
