#include <iostream>
#include <string>
#include <map>
#include <ClientSession.hpp>
#include <SessionManager.hpp>

SessionManager::SessionManager()
{

}

bool SessionManager::addSession(const int client_fd, const std::string ip)
{
    if (findSessionByFd(client_fd) != nullptr) return false;

    ClientSession client_session(client_fd, ip);

    list_sessions.insert( { client_fd, client_session } );
    return true;
}

void SessionManager::removeSession(const int client_fd)
{
    auto it = list_sessions.find(client_fd);
    if (it == list_sessions.end()) return;

    const std::string& nickname = it->second.getNickname();
    if (!nickname.empty()) used_nicknames_.erase(nickname);

    list_sessions.erase(it);
}

const ClientSession* SessionManager::findSessionByFd(const int client_fd) const
{
    auto find_key = list_sessions.find(client_fd);
    if (find_key != list_sessions.end()) return &find_key->second;

    return nullptr;
}

ClientSession* SessionManager::findSessionByFd(const int client_fd)
{
    auto find_key = list_sessions.find(client_fd);
    if (find_key != list_sessions.end()) return &find_key->second;

    return nullptr;
}

const ClientSession* SessionManager::findByNickname(const std::string& nickname) const
{
    for (const auto& pair : list_sessions)
    {
        if (pair.second.getNickname() == nickname) return &pair.second;
    }

    return nullptr;
}

bool SessionManager::isNicknameUsed(const std::string& nickname)
{
    auto used_nickname = used_nicknames_.find(nickname);
    if (used_nickname != used_nicknames_.end()) return true;

    return false;
}

bool SessionManager::setNickname(const int client_fd, const std::string& nickname)
{
    ClientSession* session = findSessionByFd(client_fd);
    if (!session) return false;

    if (isNicknameUsed(nickname)) return false;

    session->setNickname(nickname);
    used_nicknames_.insert(nickname);

    return true;
}