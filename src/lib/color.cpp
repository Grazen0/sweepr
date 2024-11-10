#include "color.h"
#include <iostream>

#if __has_include(<windows.h>)

#include <windows.h>

namespace sweepr::color {
    void reset() {
        // TODO: implementar en windows
    }

    void set_style(const Style style) {
        // TODO: implementar en windows
    }

    void set_foreground_color(const Color color) {
        // TODO: implementar para windows
    }

    void set_background_color(const Color color) {
        // TODO: implementar en windows
    }
}

#else

namespace sweepr::color {
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
