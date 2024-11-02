#include "LeaderboardEntry.h"

namespace sweepr::data {
    LeaderboardEntry::LeaderboardEntry(const std::string& name,
                                       const int turns_taken)
        : name(name), turns_taken(turns_taken) {}

    const std::string& LeaderboardEntry::get_name() const {
        return this->name;
    }

    int LeaderboardEntry::get_turns_taken() const {
        return this->turns_taken;
    }
}
