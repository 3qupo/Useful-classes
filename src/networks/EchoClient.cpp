#include <sys/socket.h>                         // Создание сокета
#include <netinet/in.h>                         // Описание адреса (IP + port)
#include <arpa/inet.h>                          // Превращает IP в понятный компьютеру формат
#include <unistd.h>                             // Закрывает соединение, чтение / запись
#include <cstring>
#include <iostream>
#include <errno.h>
#include <csignal>
#include "../../include/networks/EchoClient.hpp"
#include "database/EchoDatabase.hpp"

EchoClient::EchoClient(const std::string& ip, int port)
{
    _port = port;
    _socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket_fd == -1)
    {
        perror("Client socket failed");
        exit(1);
    }

    _server_addr.sin_family = AF_INET;
    _server_addr.sin_port = htons(_port);
    _server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
}


bool EchoClient::connectServer()
{
    socklen_t len = sizeof(_server_addr);
    int result_connect = connect(_socket_fd, (sockaddr*)& _server_addr, len);
    if (result_connect == -1)
    {
        perror("Client connect failed");
        return false;
    }

    return true;
}


bool EchoClient::sendMessage(const std::string& message)
{
    int send_message = send(_socket_fd, message.c_str(), message.length(), 0);
    if (send_message == - 1)
    {
        perror("Error send message");
        close(_socket_fd);
        return false;
    }

    return true;
}


std::string EchoClient::receiveMessage()
{
    char buffer[4096] = { 0 };

    int receive_message = recv(_socket_fd, buffer, sizeof(buffer) / sizeof(buffer[0]), 0);
    if (receive_message == -1)
    {
        perror("Error receive message");
        close(_socket_fd);
        return "";
    }

    if (receive_message == 0)
    {
        close(_socket_fd);
        return "";
    }

    return std::string(buffer, receive_message);
}


void EchoClient::closeClient()
{
    if (_socket_fd != -1)
    {
        close(_socket_fd);
        _socket_fd = -1;
    }
}