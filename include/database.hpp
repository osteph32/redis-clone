#pragma once

#include "command.hpp"
#include <unordered_map>
#include <string>
#include <chrono>

class Database {
public:
    Database();
    std::string execute(const Command& cmd);

private:
    std::unordered_map<std::string, std::string> store;

    std::unordered_map<std::string, std::chrono::system_clock::time_point> expirations;

    void saveToDisk();
    void loadFromDisk();
    bool isExpired(const std::string& key);
};