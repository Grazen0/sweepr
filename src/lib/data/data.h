#ifndef LIB_DATA
#define LIB_DATA

#include "Leaderboard.h"

namespace sweepr::data {
    constexpr int MAX_ENTRIES = 5;
    constexpr char DATA_FILENAME[] = "scores.txt";
    constexpr char ENTRY_SEPARATOR = ':';

    Leaderboard load_leaderboard();

    void save_leaderboard(Leaderboard& leaderboard);
}

#endif
