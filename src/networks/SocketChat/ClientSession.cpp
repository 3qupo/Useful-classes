#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "ClientSession.hpp"
#include "Room.hpp"

ClientSession::ClientSession(const int client_fd, const std::string& ip)
{
    client_fd_ = client_fd;
    ip_ = ip;
}

const int ClientSession::getFd() const { return client_fd_; }
const std::string& ClientSession::getNickname() const { return nickname_; }
const std::set<std::string> ClientSession::getRoomList() const { return rooms_list_; }
const std::string& ClientSession::getIp() const { return ip_; }
bool ClientSession::isAutenticated() { return is_autenticated; }

void ClientSession::setNickname(const std::string& nickname) { nickname_ = nickname; }
void ClientSession::setAutenticated(bool status) { is_autenticated = status; } 

void ClientSession::addRoom(const std::string& room_name) 
{ 
    auto hasRoom = rooms_list_.find(room_name);
    if (hasRoom != rooms_list_.end()) return;

    rooms_list_.insert(room_name);
}

void ClientSession::removeRoom(const std::string& room_name)
{
    auto hasRoom = rooms_list_.find(room_name);
    if (hasRoom == rooms_list_.end()) return;

    rooms_list_.erase(room_name);
}