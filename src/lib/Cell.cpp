#include "Cell.h"

namespace sweepr {
    Cell::Cell()
        : mine(false), flagged(false), discovered(false), adjacent_mines(0) {}

    bool Cell::is_mine() const {
        return this->mine;
    }

    void Cell::set_mine(const bool is_mine) {
        this->mine = is_mine;
    }

    bool Cell::is_flagged() const {
        return this->flagged;
    }

    bool Cell::toggle_flagged() {
        this->flagged = !this->flagged;
        return this->flagged;
    }

    bool Cell::is_discovered() const {
        return this->discovered;
    }

    void Cell::set_discovered(const bool discovered) {
        this->discovered = discovered;
    }

    int Cell::get_adjacent_mines() const {
        return this->adjacent_mines;
    }

    void Cell::increment_adjacent_mines() {
        this->adjacent_mines++;
    }
}
