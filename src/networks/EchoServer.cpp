#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <errno.h>
#include "../include/networks/EchoServer.hpp"

// -----------Server------------

EchoServer::EchoServer(int port)
{

}


void EchoServer::start()
{

}


int EchoServer::acceptClient()
{

}


void EchoServer::echoResponse(int client_fd)
{

}


void EchoServer::closeServer()
{

}


// -----------Client------------

EchoClient::EchoClient(const std::string& ip, int port)
{

}


bool EchoClient::connectServer()
{

}


void EchoClient::sendMessage(const std::string& message)
{

}


std::string EchoClient::receiveMessage()
{

}


void EchoClient::closeClient()
{

}