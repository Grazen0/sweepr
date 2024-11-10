#ifndef LIB_COLOR
#define LIB_COLOR

namespace color {
    // https://www.geeksforgeeks.org/enumeration-in-cpp/
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
