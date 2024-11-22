#ifndef LIB_DATA
#define LIB_DATA

#include "Scoreboard.h"

namespace data {
    constexpr char DATA_FILENAME[] = "scores.txt";
    constexpr char ENTRY_SEPARATOR = ':';

    Scoreboard load_scoreboard();

    void save_scoreboard(const Scoreboard& scoreboard);
}

#endif
