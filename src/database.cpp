#include "database.hpp"

#include <fstream>
#include <sstream>

Database::Database() {
    loadFromDisk();
}

bool Database::isExpired(const std::string& key) {
    auto it = expirations.find(key);

    if (it == expirations.end()) {
        return false;
    }

    if (std::chrono::system_clock::now() >= it->second) {
        store.erase(key);
        expirations.erase(key);
        saveToDisk();
        return true;
    }

    return false;
}

std::string Database::execute(const Command& cmd) {
    std::lock_guard<std::mutex> lock(db_mutex);

    switch (cmd.type) {
        case CommandType::SET: {
            store[cmd.args[0]] = cmd.args[1];
            saveToDisk();
            return "OK\n";
        }

        case CommandType::GET: {
            if (isExpired(cmd.args[0])) {
                return "(nil)\n";
            }

            auto it = store.find(cmd.args[0]);
            if (it != store.end()) {
                return it->second + "\n";
            }
            return "(nil)\n";
        }

        case CommandType::DEL: {
            size_t erased = store.erase(cmd.args[0]);
            expirations.erase(cmd.args[0]);
            saveToDisk();
            return erased ? "OK\n" : "(nil)\n";
        }

        case CommandType::EXPIRE: {
            int seconds = std::stoi(cmd.args[1]);

            expirations[cmd.args[0]] =
                std::chrono::system_clock::now() +
                std::chrono::seconds(seconds);

            return "OK\n";
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