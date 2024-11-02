#include "ScoreboardEntry.h"

namespace sweepr::data {
    ScoreboardEntry::ScoreboardEntry(const std::string& name,
                                     const int turns_taken)
        : name(name), turns_taken(turns_taken) {}

    const std::string& ScoreboardEntry::get_name() const {
        return this->name;
    }

    int ScoreboardEntry::get_turns_taken() const {
        return this->turns_taken;
    }
}
