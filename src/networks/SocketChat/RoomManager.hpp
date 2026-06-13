#pragma once

#include <iostream>
#include <string>
#include <set>
#include <map>
#include "Room.hpp"

class RoomManager
{
private:
    std::map<std::string, Room> list_rooms_;
    
public:
    RoomManager();

    bool create_room(const std::string& name);
    void delete_room(const std::string& name);
    const Room* find_room(const std::string& name) const;
    std::set<std::string> all_rooms() const;
};
