#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <errno.h>

class EchoServer
{
private:
    int _socket_fd;
    sockaddr_in _address;
    int _port;

public:
    EchoServer(int port);
    void start();
    int acceptClient();
    void echoResponse(int client_fd);
    void closeServer();


};


class EchoClient
{
private:
    int _socket_fd;
    sockaddr_in _server_addr;
    int _port;

public:
    EchoClient(const std::string& ip, int port);
    bool connectServer();
    void sendMessage(const std::string& message);
    std::string receiveMessage();
    void closeClient();
};
