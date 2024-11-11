#include <ctime>
#include <iostream>
#include "lib/color.h"
#include "lib/util.h"
#include "menu.h"

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

    bool done = false;
    std::string error_message;

    while (!done) {
        color::clear_screen();
        color::set_foreground_color(color::Color::Blue);
        color::set_style(color::Style::Bold);
        std::cout << GAME_BANNER << std::endl;
        color::reset();

        // Si no hay mensaje de error, igual se imprime la línea que ocuparía
        color::set_foreground_color(color::Color::Red);
        std::cout << error_message << std::endl;
        std::cout << std::endl;
        color::reset();
        error_message = "";

        std::cout << "Seleccione una opción:" << std::endl;
        std::cout << "1. Jugar" << std::endl;
        std::cout << "2. Mejores jugadores" << std::endl;
        std::cout << "3. Salir" << std::endl;

        const int selection = util::safe_prompt<int>();

        switch (selection) {
            case 1:
                menu::select_difficulty();
                break;
            case 2:
                menu::show_scoreboard();
                break;
            case 3:
                color::clear_screen();
                std::cout << "¡Hasta luego!" << std::endl;
                done = true;
                break;
            default:
                error_message = "Selección inválida.";
        }
    }

    return 0;
}
