#include <iostream>
#include "parser.hpp"

int main() {
    Command cmd = Parser::parse("SET car BMW");

    if (cmd.type == CommandType::SET) {
        std::cout << "SET command parsed successfully" << std::endl;
        std::cout << "Key: " << cmd.args[0] << std::endl;
        std::cout << "Value: " << cmd.args[1] << std::endl;
    } else {
        std::cout << "Invalid command" << std::endl;
    }

    return 0;
}