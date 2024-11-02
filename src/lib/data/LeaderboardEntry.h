#ifndef LIB_DATA_LEADERBOARD_ENTRY
#define LIB_DATA_LEADERBOARD_ENTRY

#include <string>

namespace sweepr::data {
    class LeaderboardEntry {
    private:
        std::string name;
        int turns_taken;

    public:
        LeaderboardEntry(const std::string& name, const int turns_taken);

        const std::string& get_name() const;

        int get_turns_taken() const;
    };
}

#endif
