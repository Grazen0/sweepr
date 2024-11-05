#include <ctime>
#include <iostream>
#include "lib/GameState.h"
#include "lib/data/Scoreboard.h"
#include "lib/data/data.h"
#include "lib/specs.h"
#include "lib/util.h"

namespace util = sweepr::util;
namespace specs = sweepr::specs;
namespace data = sweepr::data;

void print_scoreboard_section(const data::Scoreboard& scoreboard,
                              const int difficulty, const char label[]) {
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
        util::clear_screen();

        std::cout << GAME_BANNER << std::endl;

        if (!error_message.empty()) {
            std::cout << error_message << std::endl;
            std::cout << std::endl;

            error_message = "";
        }

        std::cout << "Seleccione una opción:" << std::endl;
        std::cout << "1. Jugar" << std::endl;
        std::cout << "2. Mejores jugares" << std::endl;
        std::cout << "3. Salir" << std::endl;

        int selection;
        std::cin >> selection;

        std::cout << std::endl;

        switch (selection) {
            case 1: {
                std::cout << "Seleccione la dificultad:" << std::endl;
                std::cout << "1. Fácil" << std::endl;
                std::cout << "2. Intermedio" << std::endl;
                std::cout << "3. Difícil" << std::endl;

                int difficulty;
                std::cin >> difficulty;

                while (difficulty < specs::DIFFICULTY_EASY ||
                       difficulty > specs::DIFFICULTY_HARD) {
                    std::cout << "Selección inválida." << std::endl;

                    std::cin >> difficulty;
                }

                sweepr::GameState game(difficulty);

                game.run();

                std::cout << std::endl;
                break;
            }
            case 2: {
                const data::Scoreboard scoreboard = data::load_scoreboard();

                util::clear_screen();

                std::cout << "Mejores jugadores:" << std::endl;
                std::cout << std::endl;

                print_scoreboard_section(scoreboard, specs::DIFFICULTY_EASY,
                                         "Fácil");
                print_scoreboard_section(scoreboard, specs::DIFFICULTY_MEDIUM,
                                         "Intermedio");
                print_scoreboard_section(scoreboard, specs::DIFFICULTY_HARD,
                                         "Difícil");

                std::cout << std::endl;
                std::cout << "Presiona enter para volver al menú principal...";
                util::wait_for_enter();
                break;
            }
            case 3: {
                util::clear_screen();
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
