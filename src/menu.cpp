#include "menu.h"
#include <iostream>
#include "lib/GameState.h"
#include "lib/color.h"
#include "lib/data/data.h"
#include "lib/util.h"

namespace menu {
    void print_scoreboard_section(const data::Scoreboard& scoreboard,
                                  const specs::Difficulty difficulty,
                                  const char label[]) {
        const auto& entries = scoreboard.get_entries(difficulty);

        std::cout << label << ':' << std::endl;

        for (int i = 0; i < std::min(5, (int)entries.size()); i++) {
            std::cout << (i + 1) << ". " << entries[i].get_name() << " - "
                      << entries[i].get_turns_taken() << " turnos" << std::endl;
        }

        std::cout << std::endl;
    }

    void show_scoreboard() {
        color::clear_screen();

        color::set_foreground_color(color::Color::BrightYellow);
        std::cout << "Mejores jugadores:" << std::endl;
        std::cout << std::endl;
        color::reset();

        const auto scoreboard = data::load_scoreboard();

        print_scoreboard_section(scoreboard, specs::Difficulty::Easy, "Fácil");
        print_scoreboard_section(scoreboard, specs::Difficulty::Medium,
                                 "Intermedio");
        print_scoreboard_section(scoreboard, specs::Difficulty::Hard,
                                 "Difícil");

        std::cout << std::endl;
        std::cout << "Presiona enter para volver al menú principal...";
        util::wait_for_enter();
    }

    void select_difficulty() {
        color::clear_screen();

        std::cout << "Seleccione la dificultad:" << std::endl;
        std::cout << "1. Fácil" << std::endl;
        std::cout << "2. Intermedio" << std::endl;
        std::cout << "3. Difícil" << std::endl;

        int difficulty_selection = util::safe_prompt<int>();

        while (difficulty_selection < 1 || difficulty_selection > 3) {
            std::cout << "Selección inválida." << std::endl;
            difficulty_selection = util::safe_prompt<int>();
        }

        std::cout << std::endl;

        specs::Difficulty difficulty;

        switch (difficulty_selection) {
            case 1:
                difficulty = specs::Difficulty::Easy;
                break;
            case 2:
                difficulty = specs::Difficulty::Medium;
                break;
            case 3:
                difficulty = specs::Difficulty::Hard;
                break;
        }

        GameState game(difficulty);

        game.run();
    }
}
