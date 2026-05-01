#include "server.hpp"
#include "parser.hpp"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

Server::Server(int port) : port(port) {}

void Server::start() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    std::cout << "Server listening on port " << port << std::endl;

    int addrlen = sizeof(address);
    int client_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);

    char buffer[1024] = {0};

    while (true) {
        memset(buffer, 0, sizeof(buffer));

        int bytes_read = read(client_socket, buffer, sizeof(buffer));

        if (bytes_read <= 0) {
            break;
        }

        std::string input(buffer);

        while (!input.empty() && (input.back() == '\n' || input.back() == '\r')) {
            input.pop_back();
        }

        Command cmd = Parser::parse(input);
        std::string response = db.execute(cmd);

        send(client_socket, response.c_str(), response.size(), 0);
    }

    close(client_socket);
    close(server_fd);
}