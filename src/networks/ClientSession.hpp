#pragma once

#include <iostream>
#include <string>
#include <set>
#include "RoomManager.hpp"

class ClientSession
{
private:
    int client_fd_;
    std::string nickname_;
    std::string current_room;
    std::set<std::string> rooms_list_;
    std::string ip_;

public:
    ClientSession();
    ~ClientSession();

    
};

