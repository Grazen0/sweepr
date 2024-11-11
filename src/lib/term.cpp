#include "term.h"
#include <iostream>

// https://stackoverflow.com/a/33260104/14766637
#if __has_include(<windows.h>)

#include <windows.h>

namespace term {
    void clear_screen() {
        std::system("cls");
    }

    void reset() {
        set_foreground_color(term::Color::BrightWhite);
    }

    void set_style(const Style style) {
        // No se puede en windows :(
    }

    void set_foreground_color(const Color color) {
        WORD attribute;

        switch (color) {
            case term::Black:
            default:
                attribute = 0;
                break;
            case term::Red:
                attribute = FOREGROUND_RED;
                break;
            case term::Green:
                attribute = FOREGROUND_GREEN;
                break;
            case term::Yellow:
                attribute = FOREGROUND_RED | FOREGROUND_GREEN;
                break;
            case term::Blue:
                attribute = FOREGROUND_BLUE;
                break;
            case term::Magenta:
                attribute = FOREGROUND_RED | FOREGROUND_BLUE;
                break;
            case term::Cyan:
                attribute = FOREGROUND_GREEN | FOREGROUND_BLUE;
                break;
            case term::White:
                attribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
                break;
            case term::Color::BrightBlack:
                attribute = FOREGROUND_INTENSITY;
                break;
            case term::Color::BrightRed:
                attribute = FOREGROUND_RED | FOREGROUND_INTENSITY;
                break;
            case term::Color::BrightGreen:
                attribute = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                break;
                break;
            case term::Color::BrightYellow:
                attribute =
                    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                break;
            case term::Color::BrightBlue:
                attribute = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                break;
            case term::Color::BrightMagenta:
                attribute =
                    FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                break;
            case term::Color::BrightCyan:
                attribute =
                    FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                break;
            case term::Color::BrightWhite:
                attribute = FOREGROUND_RED | FOREGROUND_GREEN |
                            FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                break;
        }

        const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, attribute);
    }
}

#else

namespace term {
    void clear_screen() {
        std::cout << "\033[2J\033[1;1H";
    }

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
}

#endif
