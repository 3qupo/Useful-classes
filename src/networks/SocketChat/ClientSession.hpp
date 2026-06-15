#pragma once

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "RoomManager.hpp"

class ClientSession
{
private:
    int client_fd_;
    std::string nickname_;
    std::set<std::string> rooms_list_;
    std::string ip_;
    bool is_autenticated;


public:
    ClientSession(const int client_fd, const std::string& ip);
    
    const int getFd() const;
    const std::string& getNickname() const;
    const std::set<std::string> getRoomList() const;
    const std::string& getIp() const;
    bool isAutenticated();

    void setNickname(const std::string& nickname);
    void setAutenticated(bool status);
    void addRoom(const std::string& room_name);
    void removeRoom(const std::string& room_name);
};

