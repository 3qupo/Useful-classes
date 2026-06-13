#pragma once

#include <iostream>
#include <string>
#include <map>
#include <set>

class Room
{
private:
    std::string name_;
    std::set<int> members_;

public:
    Room(const std::string& name_room);

    int getMemberCount() const;
    void new_client(const int client_fd);  
    void delete_client(const int client_fd);
    bool isEmpty() const;
    bool hasMember(const int client_fd) const;
    const std::string& getName() const;
    const std::set<int>& getMembers() const; 
};
