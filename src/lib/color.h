#ifndef LIB_COLOR
#define LIB_COLOR
#include <cstdlib> 

void clear_console();

namespace color {
    // https://www.geeksforgeeks.org/enum-classes-in-c-and-their-advantage-over-enum-datatype/
    enum class Color {
        Black,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White,
        BrightBlack,
        BrightRed,
        BrightGreen,
        BrightYellow,
        BrightBlue,
        BrightMagenta,
        BrightCyan,
        BrightWhite,
    };

    enum class Style {
        Bold,
        Faint,
        Italic,
        Underline
    };

    void reset();

    void set_style(const Style style);

    void set_foreground_color(const Color color);

    void set_background_color(const Color color);
}

#endif
