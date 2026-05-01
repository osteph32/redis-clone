#pragma once

#include "command.hpp"
#include <unordered_map>
#include <string>

class Database {
public:
    Database();
    std::string execute(const Command& cmd);

private:
    std::unordered_map<std::string, std::string> store;

    void saveToDisk();
    void loadFromDisk();
};