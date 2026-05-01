#include "../include/parser.hpp"
#include <cassert>

int main () {
    Command cmd = Parser::parse("SET car BMW");
    
    assert(cmd.type == CommandType::SET);
    assert(cmd.args[0] == "car");
    assert(cmd.args[1] == "BMW");

    return 0;
}