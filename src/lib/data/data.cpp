#include "data.h"
#include <fstream>
#include <string>
#include "../specs.h"
#include "ScoreboardEntry.h"

namespace data {
    ScoreboardEntry* parse_entry(const std::string& line) {
        const auto separator_index = line.find(ENTRY_SEPARATOR);

        if (separator_index == std::string::npos)
            return nullptr;

        const std::string name = line.substr(0, separator_index);

        if (name.empty())
            return nullptr;

        const std::string turns_str =
            line.substr(separator_index + 1, line.size());

        int turns;

        try {
            turns = std::stoi(turns_str);
        } catch (const std::exception& e) {
            return nullptr;
        }

        return new ScoreboardEntry(name, turns);
    }

    void parse_entry_section(Scoreboard& scoreboard, std::ifstream& file,
                             const specs::Difficulty difficulty) {
        auto& entries = scoreboard.get_entries(difficulty);
        std::string line;

        while (std::getline(file, line) && !line.empty()) {
            // Usamos un puntero por la posibilidad de no retornar nada
            ScoreboardEntry* entry = parse_entry(line);

            if (entry == nullptr)
                return;

            entries.push_back(*entry);
            delete entry;  // Ya se copió, así que normal
        }
    }

    Scoreboard load_scoreboard() {
        std::ifstream file(DATA_FILENAME);
        Scoreboard scoreboard;

        if (!file.is_open()) {
            return scoreboard;
        }

        parse_entry_section(scoreboard, file, specs::Difficulty::Easy);
        parse_entry_section(scoreboard, file, specs::Difficulty::Medium);
        parse_entry_section(scoreboard, file, specs::Difficulty::Hard);

        file.close();
        return scoreboard;
    }

    void write_scoreboard_section(Scoreboard& scoreboard,
                                  const specs::Difficulty difficulty,
                                  std::ofstream& file) {
        const auto& entries = scoreboard.get_entries(difficulty);

        for (const auto& entry : entries) {
            file << entry.get_name() << ENTRY_SEPARATOR
                 << entry.get_turns_taken() << '\n';
        }

        file << '\n';
    }

    void save_scoreboard(Scoreboard& scoreboard) {
        std::ofstream file(DATA_FILENAME);

        write_scoreboard_section(scoreboard, specs::Difficulty::Easy, file);
        write_scoreboard_section(scoreboard, specs::Difficulty::Medium, file);
        write_scoreboard_section(scoreboard, specs::Difficulty::Hard, file);
        file.close();
    }
}
