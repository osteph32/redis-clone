#pragma once

#include "database.hpp"

class Server {
public:
    explicit Server(int port);
    void start();

private:
    int port;
    Database db;
};