#pragma once

#include "command.hpp"
#include <string>

class Parser {
public:
    static Command parse(const std::string& input);
};