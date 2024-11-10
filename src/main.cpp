#include <ctime>
#include <iostream>
#include "lib/GameState.h"
#include "lib/color.h"
#include "lib/data/Scoreboard.h"
#include "lib/data/data.h"
#include "lib/specs.h"
#include "lib/util.h"

void print_scoreboard_section(
    const sweepr::data::Scoreboard& scoreboard,
    const sweepr::specs::Difficulty::Difficulty difficulty,
    const char label[]) {
    const auto& entries = scoreboard.get_entries(difficulty);

    std::cout << label << ':' << std::endl;

    for (int i = 0; i < std::min(5, (int)entries.size()); i++) {
        std::cout << (i + 1) << ". " << entries[i].get_name() << " - "
                  << entries[i].get_turns_taken() << " turnos" << std::endl;
    }

    std::cout << std::endl;
}

// https://www.geeksforgeeks.org/raw-string-literal-c/
constexpr char GAME_BANNER[] = R"(
           Bienvenido a...
 ___ __      __ ___   ___  _ __   _ __
/ __|\ \ /\ / // _ \ / _ \| '_ \ | '__|
\__ \ \ V  V /|  __/|  __/| |_) || |
|___/  \_/\_/  \___| \___|| .__/ |_|
                          |_|
)";

int main() {
    std::srand(std::time(nullptr));

    bool exit = false;
    std::string error_message;

    while (!exit) {
        sweepr::color::set_foreground_color(sweepr::color::Blue);
        sweepr::color::set_style(sweepr::color::Bold);
        std::cout << GAME_BANNER << std::endl;
        sweepr::color::reset();

        if (!error_message.empty()) {
            std::cout << error_message << std::endl;
            std::cout << std::endl;

            error_message = "";
        }

        std::cout << "Seleccione una opción:" << std::endl;
        std::cout << "1. Jugar" << std::endl;
        std::cout << "2. Mejores jugares" << std::endl;
        std::cout << "3. Salir" << std::endl;

        const int selection = sweepr::util::safe_prompt<int>();

        std::cout << std::endl;

        switch (selection) {
            case 1: {
                std::cout << "Seleccione la dificultad:" << std::endl;
                std::cout << "1. Fácil" << std::endl;
                std::cout << "2. Intermedio" << std::endl;
                std::cout << "3. Difícil" << std::endl;

                int difficulty_selection = sweepr::util::safe_prompt<int>();

                while (difficulty_selection < 1 || difficulty_selection > 3) {
                    std::cout << "Selección inválida." << std::endl;
                    difficulty_selection = sweepr::util::safe_prompt<int>();
                }

                std::cout << std::endl;

                sweepr::specs::Difficulty::Difficulty difficulty;

                switch (difficulty_selection) {
                    case 1:
                        difficulty = sweepr::specs::Difficulty::Easy;
                        break;
                    case 2:
                        difficulty = sweepr::specs::Difficulty::Medium;
                        break;
                    case 3:
                        difficulty = sweepr::specs::Difficulty::Hard;
                        break;
                }

                sweepr::GameState game(difficulty);

                game.run();

                std::cout << std::endl;
                break;
            }
            case 2: {
                const auto scoreboard = sweepr::data::load_scoreboard();

                std::cout << "Mejores jugadores:" << std::endl;
                std::cout << std::endl;

                print_scoreboard_section(
                    scoreboard, sweepr::specs::Difficulty::Easy, "Fácil");
                print_scoreboard_section(scoreboard,
                                         sweepr::specs::Difficulty::Medium,
                                         "Intermedio");
                print_scoreboard_section(
                    scoreboard, sweepr::specs::Difficulty::Hard, "Difícil");

                std::cout << std::endl;
                std::cout << "Presiona enter para volver al menú principal...";
                sweepr::util::wait_for_enter();
                break;
            }
            case 3: {
                std::cout << "¡Hasta luego!" << std::endl;
                exit = true;
                break;
            }
            default: {
                error_message = "Selección inválida.";
            }
        }
    }

    return 0;
}
