#ifndef LIB_GAME_STATE
#define LIB_GAME_STATE

#include <string>
#include "Cell.h"

namespace sweepr {
    constexpr int STATE_PLAYING = 0;
    constexpr int STATE_VICTORY = 1;
    constexpr int STATE_LOSS = 2;

    class GameState {
    private:
        const int difficulty;
        const int mine_count;
        const int board_size;
        sweepr::Cell** grid;  // Matriz de celdas

        int flag_count;
        int discovered_count;
        int state;
        bool initialized;

        int total_cells() const;

        void print_grid() const;

        void discover_cell(const int i, const int j);

        std::string do_action(const int i, const int j, const char action);

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
