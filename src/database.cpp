#include "database.hpp"

Database::Database() {}

std::string Database::execute(const Command& cmd) {
    switch (cmd.type) {
        case CommandType::SET: {
            store[cmd.args[0]] = cmd.args[1];
            return "OK";
        }

        case CommandType::GET: {
            auto it = store.find(cmd.args[0]);
            if (it != store.end()) {
                return it->second;
            }
            return "(nil)";
        }

        case CommandType::DEL: {
            size_t erased = store.erase(cmd.args[0]);
            return erased ? "OK" : "(nil)";
        }

        default:
            return "ERROR";
    }
}