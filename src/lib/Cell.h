#ifndef LIB_CELL
#define LIB_CELL

namespace sweepr {
    class Cell {
    private:
        bool mine;
        bool flagged;
        bool discovered;
        int adjacent_mines;

    public:
        Cell();

        bool is_mine() const;

        void set_mine(const bool is_mine);

        bool is_flagged() const;

        bool toggle_flagged();

        bool is_discovered() const;

        void set_discovered(const bool discovered);

        int get_adjacent_mines() const;

        void increment_adjacent_mines();
    };
}

#endif
