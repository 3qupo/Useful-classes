#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <errno.h>
#include "../../src/networks/database/EchoDatabase.hpp"


class EchoClient
{
private:
    int _socket_fd;
    sockaddr_in _server_addr;
    int _port;

public:
    EchoClient(const std::string& ip, int port);
    bool connectServer();
    bool sendMessage(const std::string& message);
    std::string receiveMessage();
    void closeClient();
};