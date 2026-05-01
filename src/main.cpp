#include <iostream>
#include "parser.hpp"
#include "database.hpp"
#include "server.hpp"

int main() {
    Server server(6379);
    server.start();
    return 0;
}