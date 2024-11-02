#include "data.h"
#include <fstream>
#include <string>
#include "../specs.h"
#include "ScoreboardEntry.h"

namespace sweepr::data {
    ScoreboardEntry* parse_entry(const std::string& line) {
        const auto separator_index = line.find(ENTRY_SEPARATOR);

        if (separator_index == std::string::npos) {
            return nullptr;  // Entry malformado
        }

        const std::string name = line.substr(0, separator_index);
        const std::string turns_str =
            line.substr(separator_index + 1, line.size());

        // TODO: handle parsing errors
        return new ScoreboardEntry(name, std::stoi(turns_str));
    }

    void parse_entry_section(Scoreboard& scoreboard, std::ifstream& file,
                             const int difficulty) {
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

        parse_entry_section(scoreboard, file, specs::DIFFICULTY_EASY);
        parse_entry_section(scoreboard, file, specs::DIFFICULTY_MEDIUM);
        parse_entry_section(scoreboard, file, specs::DIFFICULTY_HARD);

        file.close();
        return scoreboard;
    }

    void write_scoreboard_section(Scoreboard& scoreboard, const int difficulty,
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

        write_scoreboard_section(scoreboard, specs::DIFFICULTY_EASY, file);
        write_scoreboard_section(scoreboard, specs::DIFFICULTY_MEDIUM, file);
        write_scoreboard_section(scoreboard, specs::DIFFICULTY_HARD, file);
        file.close();
    }
}
