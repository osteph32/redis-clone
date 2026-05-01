#include "database.hpp"

#include <fstream>
#include <sstream>

Database::Database() {
    loadFromDisk();
}

std::string Database::execute(const Command& cmd) {
    switch (cmd.type) {
        case CommandType::SET: {
            store[cmd.args[0]] = cmd.args[1];
            saveToDisk();
            return "OK\n";
        }

        case CommandType::GET: {
            auto it = store.find(cmd.args[0]);
            if (it != store.end()) {
                return it->second + "\n";
            }
            return "(nil)\n";
        }

        case CommandType::DEL: {
            size_t erased = store.erase(cmd.args[0]);
            saveToDisk();
            return erased ? "OK\n" : "(nil)\n";
        }

        default:
            return "ERROR\n";
    }
}

void Database::saveToDisk() {
    std::ofstream file("dump.rdb");

    for (const auto& pair : store) {
        file << pair.first << ":" << pair.second << "\n";
    }
}

void Database::loadFromDisk() {
    std::ifstream file("dump.rdb");
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string key, value;

        if (std::getline(ss, key, ':') &&
            std::getline(ss, value)) {
            store[key] = value;
        }
    }
}