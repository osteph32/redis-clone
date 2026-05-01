#include "parser.hpp"
#include <sstream>
#include <vector>

Command Parser::parse(const std::string& input) {
    std::stringstream ss(input);
    std::string token;
    std::vector<std::string> tokens;

    while (ss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) {
        return {CommandType::INVALID, {}};
    }

    std::string cmd = tokens[0];

    if (cmd == "SET" && tokens.size() >= 3) {
        return {CommandType::SET, {tokens[1], tokens[2]}};
    }

    if (cmd == "GET" && tokens.size() >= 2) {
        return {CommandType::GET, {tokens[1]}};
    }

    if (cmd == "DEL" && tokens.size() >= 2) {
        return {CommandType::DEL, {tokens[1]}};
    }

    if (cmd == "EXPIRE" && tokens.size() >= 3) {
        return {CommandType::EXPIRE, {tokens[1], tokens[2]}};
    }

    if (cmd == "EXISTS" && tokens.size() >= 2) {
        return {CommandType::EXISTS, {tokens[1]}};
    }

    if (cmd == "KEYS") {
        return {CommandType::KEYS, {}};
    }

    if (cmd == "PING") {
        return {CommandType::PING, {}};
    }

    return {CommandType::INVALID, {}};
}