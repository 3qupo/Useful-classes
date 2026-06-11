#include <sys/socket.h>                         // Создание сокета
#include <netinet/in.h>                         // Описание адреса (IP + port)
#include <arpa/inet.h>                          // Превращает IP в понятный компьютеру формат
#include <unistd.h>                             // Закрывает соединение, чтение / запись
#include <cstring>
#include <iostream>
#include <errno.h>
#include <csignal>
#include "../../include/networks/EchoServer.hpp"
#include "database/EchoDatabase.hpp"
#include <thread>

EchoServer* EchoServer::_instance = nullptr;

EchoServer::EchoServer(int port)
{
    _port = port;
    _socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket_fd == -1) 
    {
        perror("Socket problem: ");
        exit(1);
    }

    _address.sin_family = AF_INET;
    _address.sin_port = htons(_port);
    _address.sin_addr.s_addr = INADDR_ANY;

    int bind_result = bind(_socket_fd, (struct sockaddr*)& _address, sizeof(_address));
    if (bind_result == -1) 
    {
        perror("Bind problem: ");
        close(_socket_fd);
        exit(1);
    }

    int listen_result = listen(_socket_fd, 128);
    if (listen_result == -1) 
    {
        perror("Problem with listen: ");
        close(_socket_fd);
        exit(1);
    }

    _running = true;
    _instance = this;
    std::signal(SIGINT, signalHandler);

    bool database_connect = _db.connect("localhost", "5433", "echo_db", "postgres", "1234");
    if (database_connect == false)
    {
        std::cerr << "Database connection failed: " << _db.getLastError() << std::endl;
        exit(1);
    }
}

void EchoServer::signalHandler(int sig)
{
    if (sig == SIGINT)
    {
        _instance->_running = false;
        close(_instance->_socket_fd);
    }
}

EchoServer::~EchoServer() 
{ 
    _db.disconnect();
    closeServer(); 
}

void EchoServer::start()
{
    std::cout << "Server is connected in the port " << _port << std::endl;

    while(_running)
    {
        int client_fd = acceptClient();
        if (client_fd == - 1) continue;
        std::thread( [this, client_fd]() { echoResponse(client_fd); } ).detach();
    }

    std::cout << "Server stopped" << std::endl;
}


int EchoServer::acceptClient()
{
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(_socket_fd, &read_fds);
    
    struct timeval timeout;
    timeout.tv_sec = 0;  
    timeout.tv_usec = 100000;
    
    int ready = select(_socket_fd + 1, &read_fds, NULL, NULL, &timeout);
    
    if (ready == -1)
    {
        if (_running) perror("select failed");
        return -1;
    }
    
    if (ready == 0) return -1;

    socklen_t address_len = sizeof(_address);
    int result_accept = accept(_socket_fd, (struct sockaddr*)& _address, &address_len);
    if (result_accept == -1 && _running) perror ("Accept failed");
    
    return result_accept;
}


void EchoServer::echoResponse(int client_fd)
{
    char buffer[4096] = { 0 };

    while (_running)
    {
        ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer) / sizeof(buffer[0]), 0);
        if (bytes_read == -1)
        {
            perror("echo read failed");
            int close_result = close(client_fd);
            if (close_result == -1) perror("Close problem: ");
            return;
        }

        if (bytes_read == 0)            // A client closed the connect 
        {
            close(client_fd);
            return;
        }

        _cout_mutex.lock();
        std::cout << "Received: " << std::string(buffer, bytes_read) << std::endl;
        _cout_mutex.unlock();

        ssize_t send_result = send(client_fd, buffer, bytes_read, 0);
        if (send_result == -1)
        {
            perror("echo send failed");
            int close_result = close(client_fd);
            if (close_result == -1) perror("Close problem: ");
            return;
        }

        std::string client_ip = inet_ntoa(_address.sin_addr);
        std::string message(buffer, bytes_read);

        _db_mutex.lock();
        bool log_success = _db.logMessage(client_ip, message);
        _db_mutex.unlock();
        if (log_success == false) std::cerr << "Failed to log a message: " << _db.getLastError() << std::endl;
    }
    
    close(client_fd);
}


void EchoServer::closeServer()
{
    if (_socket_fd != -1)
    {
        int result_close = close(_socket_fd);
        if (result_close == -1) perror("Close failed");
    }
    _socket_fd = -1;
}