#ifndef LIB_DATA_SCOREBOARD_ENTRY
#define LIB_DATA_SCOREBOARD_ENTRY

#include <string>

namespace data {
    class ScoreboardEntry {
    private:
        std::string name;
        int turns_taken;

    public:
        ScoreboardEntry(const std::string& name, const int turns_taken);

        const std::string& get_name() const;

        int get_turns_taken() const;
    };
}

#endif
