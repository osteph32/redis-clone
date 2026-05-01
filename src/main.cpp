#include <iostream>
#include "parser.hpp"
#include "database.hpp"

int main() {
    Database db;

    Command cmd1 = Parser::parse("SET car BMW");
    std::cout << db.execute(cmd1) << std::endl;

    Command cmd2 = Parser::parse("GET car");
    std::cout << db.execute(cmd2) << std::endl;

    Command cmd3 = Parser::parse("DEL car");
    std::cout << db.execute(cmd3) << std::endl;

    Command cmd4 = Parser::parse("GET car");
    std::cout << db.execute(cmd4) << std::endl;

    return 0;
}