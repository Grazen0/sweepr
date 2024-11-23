#ifndef LIB_GAME_STATE
#define LIB_GAME_STATE

#include <string>
#include "Cell.h"
#include "specs.h"

class GameState {
private:
    enum class State {
        Playing,
        Victory,
        Loss
    };

    const specs::Difficulty difficulty;
    const int mine_count;
    const int board_size;
    Cell* const* const grid;  // Matriz de celdas
    int flag_count;
    int discovered_count;
    bool initialized;
    State state;

    int total_cells() const;

    void print_grid() const;

    void discover_cell(const int i, const int j);

    void handle_win(const int turns_taken) const;

    std::string do_action(const int i, const int j, const char action);

public:
    GameState(const specs::Difficulty difficulty);

    ~GameState();

    void initialize_mines(const int safe_i, const int safe_j);

    void run();

    specs::Difficulty get_difficulty() const;

    int get_board_size() const;
};

#endif
