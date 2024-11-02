#ifndef LIB_DATA_LEADERBOARD
#define LIB_DATA_LEADERBOARD

#include <vector>
#include "LeaderboardEntry.h"

namespace sweepr::data {
    class Leaderboard {
    private:
        std::vector<LeaderboardEntry> easy_entries;
        std::vector<LeaderboardEntry> medium_entries;
        std::vector<LeaderboardEntry> hard_entries;

    public:
        std::vector<LeaderboardEntry>& get_entries(const int difficulty);

        void add_entry(const int difficulty, const std::string& name,
                       const int turns_taken);
    };
}

#endif
