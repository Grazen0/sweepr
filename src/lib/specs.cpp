#include "specs.h"
#include "util.h"

namespace specs {
    int get_board_size(const Difficulty difficulty) {
        switch (difficulty) {
            case Difficulty::Easy:
                return 6;
            case Difficulty::Medium:
                return 8;
            case Difficulty::Hard:
                return 10;
            default:
                return -1;
        }
    }

    int generate_mine_count(const Difficulty difficulty) {
        switch (difficulty) {
            case Difficulty::Easy:
                return util::rand_range(3, 5);
            case Difficulty::Medium:
                return util::rand_range(8, 12);
            case Difficulty::Hard:
                return util::rand_range(15, 20);
            default:
                return -1;
        }
    }
}
