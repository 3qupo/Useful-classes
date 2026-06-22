#pragma once

#include <string>
#include <iostream>
#include <postgresql/libpq-fe.h>
#include <map>
#include <set>
#include "Database.hpp"
#include "../SocketChat/RoomManager.hpp"
#include "../SocketChat/SessionManager.hpp"

class ChatDatabase : public Database
{
    
public:
    ChatDatabase();

    bool saveMessage(const std::string room_name, const int user_id, const std::string& message);           // Запись сообщения в БД
    bool removeMessage(const int message_id);        // Удаление записи из БД
    bool createUser(const std::string& login, const std::string& password_hash, const std::string& salt);              // Добавление пользователя в БД
    bool deleteUser(const std::string& login);           // Удаление пользователя из БД
    bool createRoom(const std::string& room_name, const std::string& creator_id);    // Добавление комнаты из БД
    bool deleteRoom(const std::string& room_name);                                // Удаление комнаты из БД
    std::string getUserHash(const std::string& login);
    std::map<int, std::string> getRoomUsers(const std::string& room_name, const int limit) const;           // <client_fd, user_name>
    bool savePrivateMessage(const int from_user, const int to_user, const std::string& message);
    bool getPrivateMessages(const int user1, const int user2, const int limit) const;
};

