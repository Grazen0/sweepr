#ifndef LIB_GAME_STATE
#define LIB_GAME_STATE

#include "Cell.h"

namespace sweepr {
    class GameState {
    private:
        const int difficulty;
        const int mine_count;
        const int board_size;
        sweepr::Cell** grid;  // Matriz de celdas

        int flag_count;
        int discovered_count;

        int total_cells() const;

        void print_grid() const;

        void discover_cell(const int i, const int j);

    public:
        GameState(const int difficulty);

        ~GameState();

        void initialize_mines(const int safe_i, const int safe_j);

        void run();

        int get_difficulty() const;

        int get_board_size() const;
    };
}

#endif
