#include "data.h"
#include <fstream>
#include <string>
#include "../specs.h"
#include "LeaderboardEntry.h"

namespace sweepr::data {
    LeaderboardEntry* parse_entry(const std::string& line) {
        const auto separator_index = line.find(ENTRY_SEPARATOR);

        if (separator_index == std::string::npos) {
            return nullptr;  // Entry malformado
        }

        const std::string name = line.substr(0, separator_index);
        const std::string turns_str =
            line.substr(separator_index + 1, line.size());

        // TODO: handle parsing errors
        return new LeaderboardEntry(name, std::stoi(turns_str));
    }

    void parse_entry_section(Leaderboard& leaderboard, std::ifstream& file,
                             const int difficulty) {
        auto& entries = leaderboard.get_entries(difficulty);
        std::string line;

        while (std::getline(file, line) && !line.empty()) {
            // Usamos un puntero por la posibilidad de no retornar nada
            LeaderboardEntry* entry = parse_entry(line);

            if (entry == nullptr)
                return;

            entries.push_back(*entry);
            delete entry;  // Ya se copió, así que normal
        }
    }

    Leaderboard load_leaderboard() {
        std::ifstream file(DATA_FILENAME);
        Leaderboard leaderboard;

        if (!file.is_open()) {
            return leaderboard;
        }

        parse_entry_section(leaderboard, file, specs::DIFFICULTY_EASY);
        parse_entry_section(leaderboard, file, specs::DIFFICULTY_MEDIUM);
        parse_entry_section(leaderboard, file, specs::DIFFICULTY_HARD);

        file.close();
        return leaderboard;
    }

    void write_leaderboard_section(Leaderboard& leaderboard,
                                   const int difficulty, std::ofstream& file) {
        const auto& entries = leaderboard.get_entries(difficulty);

        for (const auto& entry : entries) {
            file << entry.get_name() << ENTRY_SEPARATOR
                 << entry.get_turns_taken() << '\n';
        }

        file << '\n';
    }

    void save_leaderboard(Leaderboard& leaderboard) {
        std::ofstream file(DATA_FILENAME);

        write_leaderboard_section(leaderboard, specs::DIFFICULTY_EASY, file);
        write_leaderboard_section(leaderboard, specs::DIFFICULTY_MEDIUM, file);
        write_leaderboard_section(leaderboard, specs::DIFFICULTY_HARD, file);
        file.close();
    }
}
