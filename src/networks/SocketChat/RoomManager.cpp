#include <string>
#include <set>
#include <map>
#include "RoomManager.hpp"
#include "Room.hpp"

RoomManager::RoomManager() { }

bool RoomManager::create_room(const std::string& name)
{
    if (find_room(name) != nullptr) return false;

    Room room(name);
    list_rooms_.insert( { name, room } );
    return true;
}

void RoomManager::delete_room(const std::string& name)
{
    if (find_room(name) == nullptr) return;

    list_rooms_.erase(name);
} 

const Room* RoomManager::find_room(const std::string& name) const
{
    auto has_room = list_rooms_.find(name);
    if (has_room != list_rooms_.end()) return &has_room->second;
    return nullptr;
}

std::set<std::string> RoomManager::all_rooms() const
{
    std::set<std::string> list;
    for (const auto& pair : list_rooms_) list.insert(pair.first);

    return list;
}