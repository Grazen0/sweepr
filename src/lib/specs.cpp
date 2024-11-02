#include "specs.h"
#include "util.h"

namespace sweepr::specs {
    int get_board_size(const int difficulty) {
        switch (difficulty) {
            case specs::DIFFICULTY_EASY:
                return 6;
            case specs::DIFFICULTY_MEDIUM:
                return 8;
            case specs::DIFFICULTY_HARD:
                return 10;
            default:
                return -1;
        }
    }

    int generate_mine_count(const int difficulty) {
        switch (difficulty) {
            case specs::DIFFICULTY_EASY:
                return util::rand_range(3, 5);
            case specs::DIFFICULTY_MEDIUM:
                return util::rand_range(8, 12);
            case specs::DIFFICULTY_HARD:
                return util::rand_range(15, 20);
            default:
                return -1;
        }
    }
}
