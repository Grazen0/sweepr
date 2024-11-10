#ifndef LIB_SPECS
#define LIB_SPECS

namespace specs {
    enum class Difficulty {
        Easy,
        Medium,
        Hard
    };

    int get_board_size(const Difficulty difficulty);

    int generate_mine_count(const Difficulty difficulty);
}

#endif
