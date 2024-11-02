#ifndef LIB_DATA
#define LIB_DATA

#include "Scoreboard.h"

namespace sweepr::data {
    constexpr int MAX_ENTRIES = 5;
    constexpr char DATA_FILENAME[] = "scores.txt";
    constexpr char ENTRY_SEPARATOR = ':';

    Scoreboard load_scoreboard();

    void save_scoreboard(Scoreboard& scoreboard);
}

#endif
