#pragma once

#include <iostream>
#include <string>
#include <map>
#include "ClientSession.hpp"

class SessionManager
{
private:
    std::map<int, ClientSession> list_sessions;
    std::set<std::string> used_nicknames_;
    
public:
    SessionManager();

    bool addSession(const int client_fd, const std::string ip);
    void removeSession(const int client_fd);
    const ClientSession* findSessionByFd(const int client_fd) const;
    ClientSession* SessionManager::findSessionByFd(const int client_fd);
    const ClientSession* findByNickname(const std::string& nickname) const;
    bool isNicknameUsed(const std::string& nickname);
    bool setNickname(const int client_fd, const std::string& nickname);
};
