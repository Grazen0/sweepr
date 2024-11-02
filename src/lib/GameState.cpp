#include "GameState.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include "Cell.h"
#include "data/data.h"
#include "specs.h"
#include "util.h"

namespace sweepr {
    GameState::GameState(const int difficulty)
        : difficulty(difficulty),
          mine_count(specs::generate_mine_count(difficulty)),
          board_size(specs::get_board_size(difficulty)),
          flag_count(0),
          discovered_count(0),
          state(STATE_PLAYING) {
        this->grid = new Cell*[this->board_size];

        for (int i = 0; i < this->board_size; i++) {
            this->grid[i] = new Cell[this->board_size];

            for (int j = 0; j < this->board_size; j++) {
                this->grid[i][j] = Cell();
            }
        }
    }

    GameState::~GameState() {
        for (int i = 0; i < this->board_size; i++) {
            delete[] this->grid[i];
        }

        delete[] this->grid;
    }

    void GameState::print_grid() const {
        std::cout << "     ";

        for (int j = 0; j < this->board_size; j++) {
            std::cout << (j + 1) << ' ';
        }

        std::cout << std::endl;
        std::cout << "   + ";

        for (int j = 0; j < this->board_size; j++) {
            std::cout << "= ";
        }

        std::cout << std::endl;

        for (int i = 0; i < this->board_size; i++) {
            std::cout << std::setw(2) << (i + 1) << " | ";

            for (int j = 0; j < this->board_size; j++) {
                const Cell& cell = this->grid[i][j];

                switch (this->state) {
                    case STATE_PLAYING: {
                        if (cell.is_discovered()) {
                            std::cout << cell.get_adjacent_mines();
                        } else if (cell.is_flagged()) {
                            std::cout << 'F';
                        } else {
                            std::cout << '-';
                        }
                        break;
                    }
                    case STATE_VICTORY: {
                        if (cell.is_mine()) {
                            std::cout << 'F';
                        } else {
                            std::cout << cell.get_adjacent_mines();
                        }
                        break;
                    }
                    case STATE_LOSS: {
                        if (cell.is_mine()) {
                            std::cout << 'X';
                        } else if (cell.is_discovered()) {
                            std::cout << cell.get_adjacent_mines();
                        } else {
                            std::cout << '-';
                        }
                        break;
                    }
                }

                std::cout << ' ';
            }

            std::cout << std::endl;
        }
    }

    int GameState::total_cells() const {
        return this->board_size * this->board_size;
    }

    void GameState::discover_cell(const int root_i, const int root_j) {
        grid[root_i][root_j].set_discovered(true);

        std::vector<std::pair<int, int>> stack{{root_i, root_j}};

        while (!stack.empty()) {
            const auto back = stack.back();
            stack.pop_back();

            const int i = back.first;
            const int j = back.second;

            this->discovered_count++;

            if (grid[i][j].get_adjacent_mines() != 0) {
                continue;
            }

            for (int k = i - 1; k <= i + 1 && k < this->board_size; k++) {
                if (k < 0)
                    continue;

                for (int l = j - 1; l <= j + 1 && l < this->board_size; l++) {
                    if (l < 0)
                        continue;

                    auto& cell = grid[k][l];

                    if (!cell.is_discovered() && !cell.is_mine()) {
                        cell.set_discovered(true);
                        stack.push_back({k, l});
                    }
                }
            }
        }
    }

    void GameState::initialize_mines(const int start_i, const int start_j) {
        // Dato curioso: "ISO C++ forbids variable length array"
        std::vector<std::pair<int, int>> mine_candidates;
        mine_candidates.reserve(this->total_cells() - 1);

        for (int i = 0; i < this->board_size; i++) {
            for (int j = 0; j < this->board_size; j++) {
                if (i < start_i - 1 || i > start_i + 1 || j < start_j - 1 ||
                    j > start_j + 1) {
                    mine_candidates.push_back({i, j});
                }
            }
        }

        util::shuffle_first_n(mine_candidates, this->mine_count);

        for (int m = 0; m < this->mine_count; m++) {
            const auto& mine_position = mine_candidates[m];

            const int i = mine_position.first;
            const int j = mine_position.second;

            this->grid[i][j].set_mine(true);

            // Viajar por las casillas vecinas para incrementar su cuenta de
            // minas vecinas
            for (int k = i - 1; k <= i + 1 && k < this->board_size; k++) {
                if (k < 0)
                    continue;

                for (int l = j - 1; l <= j + 1 && l < this->board_size; l++) {
                    if (l < 0)
                        continue;

                    this->grid[k][l].increment_adjacent_mines();
                }
            }
        }
    }

    void GameState::run() {
        bool done = false;
        bool initialized = false;
        int turns = 0;

        std::string error_message;

        while (!done) {
            turns++;
            util::clear_screen();

            if (!error_message.empty()) {
                std::cout << error_message << std::endl;
                std::cout << std::endl;

                error_message = "";
            }

            std::cout << "Minas: " << this->mine_count
                      << " | Banderas: " << this->flag_count << std::endl;

            std::cout << std::endl;
            this->print_grid();
            std::cout << std::endl;

            if (this->state != STATE_PLAYING) {
                if (this->state == STATE_LOSS) {
                    std::cout << "¡Has descubierto una mina!" << std::endl;
                } else if (this->state == STATE_VICTORY) {
                    std::cout << "¡Felicidades! ¡Has descubierto todas las "
                                 "celdas sin mina!"
                              << std::endl;

                    data::Scoreboard scoreboard = data::load_scoreboard();

                    std::string player_name;

                    do {
                        std::cout << "Ingresa tu nombre: ";
                        std::cin >> player_name;
                    } while (player_name.find(data::ENTRY_SEPARATOR) !=
                             std::string::npos);

                    scoreboard.add_entry(this->difficulty, player_name, turns);

                    data::save_scoreboard(scoreboard);

                    std::cout << "Tu puntuación ha sido guardada en la tabla "
                                 "de puntuaciones"
                              << std::endl;
                }

                std::cout << "Presiona enter para volver al menú principal...";
                util::wait_for_enter();
                done = true;
                continue;
            }

            int i, j;
            std::cout << "Seleccione una celda (fila columna): ";
            std::cin >> i >> j;

            i--;
            j--;

            if (i < 0 || i >= this->board_size || j < 0 ||
                j >= this->board_size) {
                error_message = "Las coordenadas seleccionadas son inválidas.";
                continue;
            }

            auto& cell = this->grid[i][j];

            if (cell.is_discovered()) {
                error_message = "La casilla seleccionada ya está descubierta.";
                continue;
            }

            char action;
            std::cout
                << "Ingrese 'F' para marcar con bandera o 'D' para descubrir: ";
            std::cin >> action;

            switch (util::to_lowercase(action)) {
                case 'f': {
                    const bool is_now_flagged = cell.toggle_flagged();

                    if (is_now_flagged) {
                        this->flag_count++;
                    } else {
                        this->flag_count--;
                    }
                    break;
                }
                case 'd': {
                    if (cell.is_flagged()) {
                        error_message =
                            "La casilla seleccionada tiene bandera.";
                        break;
                    }

                    if (!initialized) {
                        this->initialize_mines(i, j);
                        initialized = true;
                    }

                    if (cell.is_mine()) {
                        this->state = STATE_LOSS;
                        break;
                    }

                    this->discover_cell(i, j);

                    if (this->discovered_count + this->mine_count ==
                        this->total_cells()) {
                        this->state = STATE_VICTORY;
                    }
                    break;
                }
                default: {
                    error_message = "La acción seleccionada es incorrecta";
                    break;
                }
            }
        }
    }

    int GameState::get_difficulty() const {
        return this->difficulty;
    }

    int GameState::get_board_size() const {
        return this->board_size;
    }
}
