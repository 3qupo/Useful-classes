#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <errno.h>
#include "../../src/networks/database/EchoDatabase.hpp"

class EchoServer
{
private:
    int _socket_fd;
    struct sockaddr_in _address;
    int _port;
    bool _running;
    EchoDatabase _db;

    static EchoServer* _instance;
    static void signalHandler(int sig);

public:
    EchoServer(int port);
    ~EchoServer();
    void start();
    int acceptClient();
    void echoResponse(int client_fd);
    void closeServer();
};
