#ifndef LIB_TERM_MANIP
#define LIB_TERM_MANIP

namespace term_manip {
    // https://stackoverflow.com/questions/17335816/clear-screen-using-c
    const char CH_CLEAR[] = "\033[2J";
    const char CH_CURSOR_RESET[] = "\033[1;1H";

    void clear_screen();

    // https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
    namespace color {
        const char RESET[] = "\033[0m";
        const char BOLD[] = "\033[1m";
        const char FAINT[] = "\033[2m";
        const char ITALIC[] = "\033[3m";
        const char UNDERLINE[] = "\033[4m";

        const char BLACK[] = "\033[30m";
        const char RED[] = "\033[31m";
        const char GREEN[] = "\033[32m";
        const char YELLOW[] = "\033[33m";
        const char BLUE[] = "\033[34m";
        const char MAGENTA[] = "\033[35m";
        const char CYAN[] = "\033[36m";
        const char WHITE[] = "\033[37m";
        const char BRIGHT_BLACK[] = "\033[90m";
        const char BRIGHT_RED[] = "\033[91m";
        const char BRIGHT_GREEN[] = "\033[92m";
        const char BRIGHT_YELLOW[] = "\033[93m";
        const char BRIGHT_BLUE[] = "\033[94m";
        const char BRIGHT_MAGENTA[] = "\033[95m";
        const char BRIGHT_CYAN[] = "\033[96m";
        const char BRIGHT_WHITE[] = "\x1B[97m";

        const char BG_BLACK[] = "\033[40m";
        const char BG_RED[] = "\033[41m";
        const char BG_GREEN[] = "\033[42m";
        const char BG_YELLOW[] = "\033[43m";
        const char BG_BLUE[] = "\033[44m";
        const char BG_MAGENTA[] = "\033[45m";
        const char BG_CYAN[] = "\033[46m";
        const char BG_WHITE[] = "\033[47m";
        const char BG_BRIGHT_BLACK[] = "\033[100m";
        const char BG_BRIGHT_RED[] = "\033[101m";
        const char BG_BRIGHT_GREEN[] = "\033[102m";
        const char BG_BRIGHT_YELLOW[] = "\033[103m";
        const char BG_BRIGHT_BLUE[] = "\033[104m";
        const char BG_BRIGHT_MAGENTA[] = "\033[105m";
        const char BG_BRIGHT_CYAN[] = "\033[106m";
        const char BG_BRIGHT_WHITE[] = "\033[107m";
    }
}

#endif
