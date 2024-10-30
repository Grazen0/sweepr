#include "specs.h"
#include "util.h"

int sweepr::specs::get_board_size(const int difficulty) {
    switch (difficulty) {
        case sweepr::specs::DIFFICULTY_EASY:
            return 6;
        case sweepr::specs::DIFFICULTY_MEDIUM:
            return 8;
        case sweepr::specs::DIFFICULTY_HARD:
            return 10;
        default:
            return -1;
    }
}

int sweepr::specs::generate_mine_count(const int difficulty) {
    switch (difficulty) {
        case sweepr::specs::DIFFICULTY_EASY:
            return sweepr::util::rand_range(3, 5);
        case sweepr::specs::DIFFICULTY_MEDIUM:
            return sweepr::util::rand_range(8, 12);
        case sweepr::specs::DIFFICULTY_HARD:
            return sweepr::util::rand_range(15, 20);
        default:
            return -1;
    }
}
