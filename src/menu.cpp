#include "menu.h"
#include <iostream>
#include "lib/GameState.h"
#include "lib/data/data.h"
#include "lib/term.h"
#include "lib/util.h"

namespace menu {
    void print_scoreboard_section(const data::Scoreboard& scoreboard,
                                  const specs::Difficulty difficulty,
                                  const char label[]) {
        const auto& entries = scoreboard.get_entries(difficulty);

        std::cout << label << ':' << std::endl;

        for (unsigned long i = 0; i < entries.size(); i++) {
            const auto& entry = entries[i];

            std::cout << (i + 1) << ". " << entry.get_name() << " - "
                      << entry.get_turns_taken() << " turno(s)" << std::endl;
        }

        std::cout << std::endl;
    }

    void show_scoreboard() {
        term::clear_screen();

        term::set_foreground_color(term::Color::BrightYellow);
        std::cout << "Mejores jugadores:" << std::endl;
        std::cout << std::endl;
        term::reset();

        const auto scoreboard = data::load_scoreboard();

        print_scoreboard_section(scoreboard, specs::Difficulty::Easy, "Fácil");
        print_scoreboard_section(scoreboard, specs::Difficulty::Medium,
                                 "Intermedio");
        print_scoreboard_section(scoreboard, specs::Difficulty::Hard,
                                 "Difícil");

        std::cout << std::endl;
        std::cout << "Presiona enter para volver al menú principal...";
        term::wait_for_enter();
    }

    void select_difficulty() {
        term::clear_screen();

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
