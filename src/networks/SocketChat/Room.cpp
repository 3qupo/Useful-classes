#include <iostream>
#include <set>
#include <string>
#include "Room.hpp"

Room::Room(const std::string& name_room)
{
    name_ = name_room;
}

int Room::getMemberCount() const 
{
    if (isEmpty() == true) return 0;

    return members_.size();
}

void Room::new_client(const int client_fd)
{
    if (hasMember(client_fd)) return;

    members_.emplace(client_fd);
}

void Room::delete_client(const int client_fd)
{
    if (!hasMember(client_fd)) return;

    members_.erase(client_fd);
}

bool Room::isEmpty() const
{
    if (members_.size() == 0) return true;
    return false;
}

bool Room::hasMember(const int client_fd) const
{
    auto has_memeber = members_.find(client_fd);      
    if (has_memeber != members_.end()) return true;

    return false;
}

const std::string& Room::getName() const
{
    return name_;
}

const std::set<int>& Room::getMembers() const
{
    return members_;
}