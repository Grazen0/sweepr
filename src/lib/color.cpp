#include "color.h"
#include <iostream>

// https://stackoverflow.com/a/33260104/14766637
#if __has_include(<windows.h>)

#include <windows.h>

void clearConsole() {
    #ifdef _WIN32
        system("cls");  // Comando para limpiar la consola en Windows
    #elif __linux__ || __APPLE__
        system("clear");  // Comando para limpiar la consola en Linux o macOS
    #else
        std::cout << "Clear console no soportado para este sistema operativo." << std::endl;
    #endif
}

namespace color {

    WORD getWindowsColorAttribute(const Color color) {
        switch (color) {
            case Color::Black: return 0;
            case Color::Red: return FOREGROUND_RED;
            case Color::Green: return FOREGROUND_GREEN;
            case Color::Yellow: return FOREGROUND_RED | FOREGROUND_GREEN;
            case Color::Blue: return FOREGROUND_BLUE;
            case Color::Magenta: return FOREGROUND_RED | FOREGROUND_BLUE;
            case Color::Cyan: return FOREGROUND_GREEN | FOREGROUND_BLUE;
            case Color::White: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            case Color::BrightBlack: return FOREGROUND_INTENSITY;
            case Color::BrightRed: return FOREGROUND_RED | FOREGROUND_INTENSITY;
            case Color::BrightGreen: return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            case Color::BrightYellow: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            case Color::BrightBlue: return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            case Color::BrightMagenta: return FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            case Color::BrightCyan: return FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            case Color::BrightWhite: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            default: return 0;
        }
    }

    void reset() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }

    void set_style(const Style style) {
        // TODO: implementar en windows
    }

    void set_foreground_color(const Color color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, getWindowsColorAttribute(color));
    }

    void set_background_color(const Color color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD foreground = getWindowsColorAttribute(color) << 4;
        SetConsoleTextAttribute(hConsole, foreground);
    }
}

#else

namespace color {
    void reset() {
        std::cout << "\033[0m";
    }

    void set_style(const Style style) {
        switch (style) {
            case Style::Bold:
                std::cout << "\033[1m";
                break;
            case Style::Faint:
                std::cout << "\033[2m";
                break;
            case Style::Italic:
                std::cout << "\033[3m";
                break;
            case Style::Underline:
                std::cout << "\033[4m";
                break;
        }
    }

    // https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
    void set_foreground_color(const Color color) {
        switch (color) {
            case Color::Black:
                std::cout << "\033[30m";
                break;
            case Color::Red:
                std::cout << "\033[31m";
                break;
            case Color::Green:
                std::cout << "\033[32m";
                break;
            case Color::Yellow:
                std::cout << "\033[33m";
                break;
            case Color::Blue:
                std::cout << "\033[34m";
                break;
            case Color::Magenta:
                std::cout << "\033[35m";
                break;
            case Color::Cyan:
                std::cout << "\033[36m";
                break;
            case Color::White:
                std::cout << "\033[37m";
                break;
            case Color::BrightBlack:
                std::cout << "\033[90m";
                break;
            case Color::BrightRed:
                std::cout << "\033[91m";
                break;
            case Color::BrightGreen:
                std::cout << "\033[92m";
                break;
            case Color::BrightYellow:
                std::cout << "\033[93m";
                break;
            case Color::BrightBlue:
                std::cout << "\033[94m";
                break;
            case Color::BrightMagenta:
                std::cout << "\033[95m";
                break;
            case Color::BrightCyan:
                std::cout << "\033[96m";
                break;
            case Color::BrightWhite:
                std::cout << "\x1B[97m";
                break;
        }
    }

    void set_background_color(const Color color) {
        switch (color) {
            case Color::Black:
                std::cout << "\033[40m";
                break;
            case Color::Red:
                std::cout << "\033[41m";
                break;
            case Color::Green:
                std::cout << "\033[42m";
                break;
            case Color::Yellow:
                std::cout << "\033[43m";
                break;
            case Color::Blue:
                std::cout << "\033[44m";
                break;
            case Color::Magenta:
                std::cout << "\033[45m";
                break;
            case Color::Cyan:
                std::cout << "\033[46m";
                break;
            case Color::White:
                std::cout << "\033[47m";
                break;
            case Color::BrightBlack:
                std::cout << "\033[100m";
                break;
            case Color::BrightRed:
                std::cout << "\033[101m";
                break;
            case Color::BrightGreen:
                std::cout << "\033[102m";
                break;
            case Color::BrightYellow:
                std::cout << "\033[103m";
                break;
            case Color::BrightBlue:
                std::cout << "\033[104m";
                break;
            case Color::BrightMagenta:
                std::cout << "\033[105m";
                break;
            case Color::BrightCyan:
                std::cout << "\033[106m";
                break;
            case Color::BrightWhite:
                std::cout << "\033[107m";
                break;
            default:
                break;
        }
    }
}

#endif
