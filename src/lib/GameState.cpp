#include "GameState.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "Cell.h"
#include "specs.h"
#include "util.h"

sweepr::GameState::GameState(const int difficulty)
    : difficulty(difficulty),
      mine_count(specs::generate_mine_count(difficulty)),
      board_size(specs::get_board_size(difficulty)),
      flag_count(0),
      discovered_count(0) {
    this->grid = new Cell*[this->board_size];

    for (int i = 0; i < this->board_size; i++) {
        this->grid[i] = new Cell[this->board_size];
    }
}

sweepr::GameState::~GameState() {
    for (int i = 0; i < this->board_size; i++) {
        delete[] this->grid[i];
    }

    delete[] this->grid;
}

void sweepr::GameState::print_grid() const {
    for (int i = 0; i < this->board_size; i++) {
        for (int j = 0; j < this->board_size; j++) {
            const Cell cell = grid[i][j];

            if (cell.is_discovered())
                std::cout << std::to_string(cell.get_adjacent_mines());
            else if (cell.is_flagged())
                std::cout << 'F';
            else
                std::cout << '-';

            std::cout << ' ';
        }

        std::cout << std::endl;
    }
}

int sweepr::GameState::total_cells() const {
    return this->board_size * this->board_size;
}

void sweepr::GameState::discover_cell(const int root_i, const int root_j) {
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

        for (int k = i - 1; k <= i + 1; k++) {
            if (k < 0 || k >= this->board_size - 1)
                continue;

            for (int l = -1; l <= j + 1; l++) {
                if (l < 0 || l >= this->board_size - 1)
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

void sweepr::GameState::initialize() {
    // Dato curioso: "ISO C++ forbids variable length array"
    int* mine_candidates = new int[this->total_cells()];

    for (int i = 0; i < this->total_cells(); i++) {
        mine_candidates[i] = i;
    }

    util::shuffle_first_n(mine_candidates, this->total_cells(),
                          this->mine_count);

    for (int m = 0; m < this->mine_count; m++) {
        const int mine_position = mine_candidates[m];

        const int i = mine_position / this->board_size;
        const int j = mine_position % this->board_size;

        this->grid[i][j].set_mine(true);

        // Viajar por las casillas vecinas para incrementar su cuenta de minas
        // vecinas
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

void sweepr::GameState::run() {
    bool done = false;

    std::string error_message;

    while (!done) {
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

        int i, j;
        std::cout << "Seleccione una celda (fila columna): ";
        std::cin >> i >> j;

        i--;
        j--;

        if (i < 0 || i >= this->board_size || j < 0 || j >= this->board_size) {
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
                    error_message = "La casilla seleccionada tiene bandera.";
                    continue;
                }

                if (cell.is_mine()) {
                    std::cout << "¡Has descubierto una mina!" << std::endl;
                    std::cout << std::endl;

                    // TODO: show end result and prompt for enter to continue

                    done = true;
                    break;
                }

                this->discover_cell(i, j);

                if (this->discovered_count + this->mine_count ==
                    this->total_cells()) {
                    std::cout << "¡Felicidades! ¡Has descubierto todas las "
                                 "celdas sin mina!"
                              << std::endl;

                    // TODO: flag remaining cells and show end result

                    std::string player_name;
                    std::cout << "Ingresa tu nombre: ";
                    std::cin >> player_name;

                    done = true;
                }
                break;
            }
            default: {
                error_message = "La acción seleccionada es incorrecta";
                continue;
            }
        }
    }
}

int sweepr::GameState::get_difficulty() const {
    return this->difficulty;
}

int sweepr::GameState::get_board_size() const {
    return this->board_size;
}
