#include "GameState.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include "Cell.h"
#include "data/data.h"
#include "specs.h"
#include "term.h"
#include "util.h"

void print_flag() {
    term::set_foreground_color(term::Color::BrightRed);
    term::set_style(term::Style::Bold);
    std::cout << 'F';
    term::reset();
}

void print_mine() {
    term::set_foreground_color(term::Color::Red);
    term::set_style(term::Style::Bold);
    std::cout << 'X';
    term::reset();
}

void print_undiscovered() {
    term::set_foreground_color(term::Color::White);
    std::cout << '-';
    term::reset();
}

void print_number(const int n) {
    switch (n) {
        case 0:
            term::set_foreground_color(term::Color::BrightBlack);
            break;
        case 1:
            term::set_foreground_color(term::Color::BrightBlue);
            break;
        case 2:
            term::set_foreground_color(term::Color::BrightGreen);
            break;
        case 3:
            term::set_foreground_color(term::Color::Red);
            break;
        case 4:
            term::set_foreground_color(term::Color::BrightMagenta);
            break;
        case 5:
            term::set_foreground_color(term::Color::Green);
            break;
        case 6:
            term::set_foreground_color(term::Color::Cyan);
            break;
        case 7:
            term::set_foreground_color(term::Color::Blue);
            break;
        case 8:
            term::set_foreground_color(term::Color::Magenta);
            break;
    }

    std::cout << n;
    term::reset();
}

Cell** create_grid(const int size) {
    Cell** grid = new Cell*[size];

    for (int i = 0; i < size; i++) {
        grid[i] = new Cell[size];
    }

    return grid;
}

GameState::GameState(const specs::Difficulty difficulty)
    : difficulty(difficulty),
      mine_count(specs::generate_mine_count(difficulty)),
      board_size(specs::get_board_size(difficulty)),
      grid(create_grid(this->board_size)),
      flag_count(0),
      discovered_count(0),
      initialized(false),
      state(State::Playing) {}

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
                case State::Playing: {
                    if (cell.is_discovered()) {
                        print_number(cell.get_adjacent_mines());
                    } else if (cell.is_flagged()) {
                        print_flag();
                    } else {
                        print_undiscovered();
                    }
                    break;
                }
                case State::Victory: {
                    if (cell.is_mine()) {
                        print_flag();
                    } else {
                        print_number(cell.get_adjacent_mines());
                    }
                    break;
                }
                case State::Loss: {
                    if (cell.is_mine()) {
                        print_mine();
                    } else if (cell.is_flagged()) {
                        print_flag();
                    } else if (cell.is_discovered()) {
                        print_number(cell.get_adjacent_mines());
                    } else {
                        print_undiscovered();
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

                if (!cell.is_discovered() && !cell.is_mine() &&
                    !cell.is_flagged()) {
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
    mine_candidates.reserve(this->total_cells() - 9);

    for (int i = 0; i < this->board_size; i++) {
        for (int j = 0; j < this->board_size; j++) {
            if (i < start_i - 1 || i > start_i + 1 || j < start_j - 1 ||
                j > start_j + 1) {
                mine_candidates.push_back({i, j});
            }
        }
    }

    util::partial_shuffle(mine_candidates, this->mine_count);

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

std::string GameState::do_action(const int i, const int j, const char action) {
    auto& cell = this->grid[i][j];

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
                return "La casilla seleccionada tiene bandera.";
                break;
            }

            if (!this->initialized) {
                this->initialize_mines(i, j);
                this->initialized = true;
            }

            if (cell.is_mine()) {
                this->state = State::Loss;
                break;
            }

            this->discover_cell(i, j);

            if (this->discovered_count + this->mine_count ==
                this->total_cells()) {
                this->state = State::Victory;
            }
            break;
        }
        default: {
            return "La acción seleccionada es incorrecta";
            break;
        }
    }

    return "";
}

void GameState::run() {
    bool done = false;
    int turns = 0;

    std::string error_message;

    while (!done) {
        term::clear_screen();

        if (!error_message.empty()) {
            term::set_foreground_color(term::Color::Yellow);
            std::cout << ":( " << error_message << std::endl;
            term::reset();
        } else {
            std::cout << ":)" << std::endl;
            turns++;
        }

        std::cout << std::endl;

        if (!error_message.empty()) {
            error_message.clear();
        }

        std::cout << "Turno: " << turns << std::endl;
        std::cout << "Minas: " << this->mine_count << " | "
                  << "Banderas: " << this->flag_count << std::endl;

        std::cout << std::endl;
        this->print_grid();
        std::cout << std::endl;

        if (this->state != State::Playing) {
            if (this->state == State::Loss) {
                std::cout << "¡Has descubierto una mina!" << std::endl;
            } else if (this->state == State::Victory) {
                std::cout << "¡Felicidades! ¡Has descubierto todas las "
                             "celdas sin mina!"
                          << std::endl;

                data::Scoreboard scoreboard = data::load_scoreboard();

                std::string player_name;

                while (true) {
                    std::cout << "Ingresa tu nombre: ";
                    player_name = util::safe_prompt<std::string>();

                    if (player_name.empty()) {
                        std::cout << "Tu nombre no puede estar vacío."
                                  << std::endl;
                        continue;
                    }

                    break;
                }

                scoreboard.add_entry(this->difficulty, player_name, turns);

                data::save_scoreboard(scoreboard);

                std::cout << std::endl;
                std::cout << "Tu puntuación ha sido guardada en la tabla "
                             "de puntuaciones"
                          << std::endl;
            }

            std::cout << std::endl;
            std::cout << "Presiona enter para volver al menú principal...";
            term::wait_for_enter();
            done = true;
            continue;
        }

        std::cout << "Seleccione una celda (fila columna): ";
        const int i = util::safe_prompt<int>() - 1;
        const int j = util::safe_prompt<int>() - 1;

        if (i < 0 || i >= this->board_size || j < 0 || j >= this->board_size) {
            error_message = "Las coordenadas seleccionadas son inválidas.";
            continue;
        }

        auto& cell = this->grid[i][j];

        if (cell.is_discovered()) {
            error_message = "La casilla seleccionada ya está descubierta.";
            continue;
        }

        std::cout << "Ingrese 'F' para marcar (o desmarcar) una bandera o 'D' "
                     "para descubrir: ";
        const char action = util::safe_prompt<char>();

        std::cout << std::endl;

        error_message = this->do_action(i, j, action);
    }
}

specs::Difficulty GameState::get_difficulty() const {
    return this->difficulty;
}

int GameState::get_board_size() const {
    return this->board_size;
}
