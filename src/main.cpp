#include <ctime>
#include <iostream>
#include "lib/GameState.h"
#include "lib/specs.h"
#include "lib/util.h"

// `constexpr` es como `const`, pero garantiza que la variable se evalúe en el
// tiempo de compilación.
constexpr char GAME_BANNER[] =
    "            Bienvenido a...         \n"
    " ___ __      __ ___   ___  _ __   _ __ \n"
    "/ __|\\ \\ /\\ / // _ \\ / _ \\| '_ \\ | '__|\n"
    "\\__ \\ \\ V  V /|  __/|  __/| |_) || |   \n"
    "|___/  \\_/\\_/  \\___| \\___|| .__/ |_|   \n"
    "                          |_|          \n"
    "\n";

int main() {
    std::srand(std::time(nullptr));

    std::cout << std::endl;

    bool exit = false;
    std::string error_message;

    while (!exit) {
        sweepr::util::clear_screen();

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

                if (difficulty < sweepr::specs::DIFFICULTY_EASY ||
                    difficulty > sweepr::specs::DIFFICULTY_HARD) {
                    std::cout << "Selección inválida." << std::endl;
                    std::cout << std::endl;
                }

                sweepr::GameState game(difficulty);

                game.run();

                std::cout << std::endl;
                break;
            }
            case 2: {
                std::cerr << "SIN IMPLEMENTAR" << std::endl;
                std::cout << std::endl;
                break;
            }
            case 3: {
                sweepr::util::clear_screen();
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
