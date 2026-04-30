#pragma once

#include <vector>
#include <string>

enum class CommandType {
    SET,
    GET,
    DEL,
    INVALID
};

struct Command {
    CommandType type;
    std::vector<std::string> args;
};