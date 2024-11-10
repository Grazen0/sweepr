#ifndef LIB_DATA_SCOREBOARD
#define LIB_DATA_SCOREBOARD

#include <vector>
#include "../specs.h"
#include "ScoreboardEntry.h"

namespace data {
    class Scoreboard {
    private:
        std::vector<ScoreboardEntry> easy_entries;
        std::vector<ScoreboardEntry> medium_entries;
        std::vector<ScoreboardEntry> hard_entries;

    public:
        std::vector<ScoreboardEntry>& get_entries(
            const specs::Difficulty difficulty);

        const std::vector<ScoreboardEntry>& get_entries(
            const specs::Difficulty difficulty) const;

        void add_entry(const specs::Difficulty difficulty,
                       const std::string& name, const int turns_taken);
    };
}

#endif
