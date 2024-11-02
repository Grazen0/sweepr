#include "data.h"
#include <fstream>
#include "../specs.h"

namespace sweepr::data {
    Leaderboard load_leaderboard() {
        std::ifstream file(DATA_FILENAME);

        if (!file.is_open()) {
            return Leaderboard();
        }

        Leaderboard leaderboard;

        // TODO: parse scores file

        file.close();
        return leaderboard;
    }

    void save_leaderboard(Leaderboard& leaderboard) {
        std::ofstream file(DATA_FILENAME);

        for (const auto& entry :
             leaderboard.get_entries(specs::DIFFICULTY_EASY)) {
            file << entry.get_name() << '\0' << entry.get_turns_taken() << '\n';
        }

        file << '\n';

        for (const auto& entry :
             leaderboard.get_entries(specs::DIFFICULTY_MEDIUM)) {
            file << entry.get_name() << '\0' << entry.get_turns_taken() << '\n';
        }

        file << '\n';

        for (const auto& entry :
             leaderboard.get_entries(specs::DIFFICULTY_HARD)) {
            file << entry.get_name() << '\0' << entry.get_turns_taken() << '\n';
        }

        file.close();
    }
}
