#include "Scoreboard.h"
#include <vector>
#include "../specs.h"
#include "ScoreboardEntry.h"
#include "data.h"

namespace sweepr::data {
    std::vector<ScoreboardEntry>& Scoreboard::get_entries(
        const int difficulty) {
        switch (difficulty) {
            case specs::DIFFICULTY_EASY:
                return this->easy_entries;
            case specs::DIFFICULTY_MEDIUM:
                return this->medium_entries;
            case specs::DIFFICULTY_HARD:
            default:  // No debería ser así, pero no hay de otra
                return this->hard_entries;
        }
    }

    void Scoreboard::add_entry(const int difficulty, const std::string& name,
                               const int turns_taken) {
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
