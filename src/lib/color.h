#ifndef LIB_COLOR
#define LIB_COLOR

namespace sweepr::color {
    // https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
    constexpr char RESET[] = "\033[0m";
    constexpr char BOLD[] = "\033[1m";
    constexpr char FAINT[] = "\033[2m";
    constexpr char ITALIC[] = "\033[3m";
    constexpr char UNDERLINE[] = "\033[4m";
    constexpr char FG_BLACK[] = "\033[30m";
    constexpr char FG_RED[] = "\033[31m";
    constexpr char FG_GREEN[] = "\033[32m";
    constexpr char FG_YELLOW[] = "\033[33m";
    constexpr char FG_BLUE[] = "\033[34m";
    constexpr char FG_MAGENTA[] = "\033[35m";
    constexpr char FG_CYAN[] = "\033[36m";
    constexpr char FG_WHITE[] = "\033[37m";
    constexpr char FG_BRIGHT_BLACK[] = "\033[90m";
    constexpr char FG_BRIGHT_RED[] = "\033[91m";
    constexpr char FG_BRIGHT_GREEN[] = "\033[92m";
    constexpr char FG_BRIGHT_YELLOW[] = "\033[93m";
    constexpr char FG_BRIGHT_BLUE[] = "\033[94m";
    constexpr char FG_BRIGHT_MAGENTA[] = "\033[95m";
    constexpr char FG_BRIGHT_CYAN[] = "\033[96m";
    constexpr char FG_BRIGHT_WHITE[] = "\x1B[97m";
    constexpr char BG_BLACK[] = "\033[40m";
    constexpr char BG_RED[] = "\033[41m";
    constexpr char BG_GREEN[] = "\033[42m";
    constexpr char BG_YELLOW[] = "\033[43m";
    constexpr char BG_BLUE[] = "\033[44m";
    constexpr char BG_MAGENTA[] = "\033[45m";
    constexpr char BG_CYAN[] = "\033[46m";
    constexpr char BG_WHITE[] = "\033[47m";
    constexpr char BG_BRIGHT_BLACK[] = "\033[100m";
    constexpr char BG_BRIGHT_RED[] = "\033[101m";
    constexpr char BG_BRIGHT_GREEN[] = "\033[102m";
    constexpr char BG_BRIGHT_YELLOW[] = "\033[103m";
    constexpr char BG_BRIGHT_BLUE[] = "\033[104m";
    constexpr char BG_BRIGHT_MAGENTA[] = "\033[105m";
    constexpr char BG_BRIGHT_CYAN[] = "\033[106m";
    constexpr char BG_BRIGHT_WHITE[] = "\033[107m";
}

#endif
