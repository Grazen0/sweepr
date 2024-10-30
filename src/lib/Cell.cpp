#include "Cell.h"

sweepr::Cell::Cell()
    : mine(false), flagged(false), discovered(false), adjacent_mines(0) {}

bool sweepr::Cell::is_mine() const {
    return this->mine;
}

void sweepr::Cell::set_mine(const bool is_mine) {
    this->mine = is_mine;
}

bool sweepr::Cell::is_flagged() const {
    return this->flagged;
}

bool sweepr::Cell::toggle_flagged() {
    this->flagged = !this->flagged;
    return this->flagged;
}

bool sweepr::Cell::is_discovered() const {
    return this->discovered;
}

void sweepr::Cell::set_discovered(const bool discovered) {
    this->discovered = discovered;
}

int sweepr::Cell::get_adjacent_mines() const {
    return this->adjacent_mines;
}

void sweepr::Cell::increment_adjacent_mines() {
    this->adjacent_mines++;
}
