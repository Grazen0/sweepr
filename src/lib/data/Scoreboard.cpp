#include "Scoreboard.h"
#include <vector>
#include "../specs.h"
#include "ScoreboardEntry.h"
#include "data.h"

namespace data {
    std::vector<ScoreboardEntry>& Scoreboard::get_entries(
        const specs::Difficulty difficulty) {
        switch (difficulty) {
            case specs::Difficulty::Easy:
                return this->easy_entries;
            case specs::Difficulty::Medium:
                return this->medium_entries;
            case specs::Difficulty::Hard:
            default:  // Este caso no ocurre, pero sino hay un warning
                return this->hard_entries;
        }
    }

    const std::vector<ScoreboardEntry>& Scoreboard::get_entries(
        const specs::Difficulty difficulty) const {
        switch (difficulty) {
            case specs::Difficulty::Easy:
                return this->easy_entries;
            case specs::Difficulty::Medium:
                return this->medium_entries;
            case specs::Difficulty::Hard:
            default:  // Este caso no ocurre, pero sino hay un warning
                return this->hard_entries;
        }
    }

    void Scoreboard::add_entry(const specs::Difficulty difficulty,
                               const std::string& name, const int turns_taken) {
        std::vector<ScoreboardEntry>& target_vec =
            this->get_entries(difficulty);

        auto it = target_vec.begin();

        while (it != target_vec.end() && it->get_turns_taken() <= turns_taken) {
            ++it;
        }

        target_vec.insert(it, ScoreboardEntry(name, turns_taken));

        if (target_vec.size() > MAX_ENTRIES) {
            target_vec.pop_back();
        }
    }
}
