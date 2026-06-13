#pragma once

#include <iostream>
#include <string>
#include <set>
#include <map>
#include "Room.hpp"

class RoomManager
{
private:
    std::map<std::string, Room> list_rooms;
    
public:
    RoomManager();
    ~RoomManager();

    bool create_room(const std::string& name);
    void delete_room(const std::string& name);
    Room* find_room(const std::string& name) const;
    std::set<std::string> list_rooms() const;
};
