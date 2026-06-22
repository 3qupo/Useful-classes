#include <iostream>
#include <string>
#include <postgresql/libpq-fe.h>
#include "ChatDatabase.hpp"
#include "Database.hpp"

ChatDatabase::ChatDatabase()
{
    
}

bool ChatDatabase::saveMessage(const std::string room_name, const int user_id, const std::string& message)
{
    if (isConnected() == false) return false;

    std::string safe_room = escapeString(room_name);
    std::string safe_msg = escapeString(message);

    std::string sql = "INSERT INTO room_messages (room_name, user_id, message) VALUES('" + safe_room + "', " + std::to_string(user_id) + ", '" + safe_msg + "')";
    
    return executeQuery(sql);
}

bool ChatDatabase::removeMessage(const int message_id)
{
    if (isConnected() == false) return false;

    std::string sql = "DELETE FROM room_messages WHERE message_id = " + std::to_string(message_id) + ";";

    return executeQuery(sql);
}

bool ChatDatabase::createUser(const std::string& login, const std::string& password_hash, const std::string& salt)
{
    if (isConnected() == false) return false;
    
    std::string safe_login = escapeString(login);
    std::string safe_hash = escapeString(password_hash);
    std::string safe_salt = escapeString(salt);

    std::string sql = "INSERT INTO users (login, password_hash, salt)VALUES('" + safe_login + "', '" + safe_hash + "', '" + safe_salt + "')";

    return executeQuery(sql);
}

bool ChatDatabase::deleteUser(const std::string& login)
{
    if (isConnected() == false) return false;

    std::string safe_login = escapeString(login);
    std::string sql = "DELETE FROM users WHERE login = '" + safe_login + "';";

    return executeQuery(sql);
}

bool ChatDatabase::createRoom(const std::string& room_name, const std::string& creator_id)
{
    if (isConnected() == false) return false;

    std::string safe_room = escapeString(room_name);
    std::string safe_creator = escapeString(creator_id);

    std::string sql = "INSERT INTO rooms (room_name, creator_id) VALUES ('" + safe_room + "', '" + safe_creator + "')";

    return executeQuery(sql);
}

bool ChatDatabase::deleteRoom(const std::string& room_name)
{
    if (isConnected() == false) return false;

    std::string safe_room = escapeString(room_name);

    std::string sql = "DELETE FROM rooms WHERE room_name = '" + safe_room + "';";
    
    return executeQuery(sql);
}

std::pair<std::string, std::string> ChatDatabase::getUserHash(const std::string& login)
{
    if (isConnected() == false) return getLastError();

    std::string safe_login = escapeString(login);

    std::string sql = "SELECT password_hash, salt FROM users WHERE login = '" + safe_login + "' ";
    PGresult* result_request = executeQueryWithResult(sql);

    if (result_request == nullptr) return "";

    std::string getHash = PQgetvalue(result_request, 0, 0);
    std::string getSalt = PQgetvalue(result_request, 0, 1);

    PQclear(result_request);
    
    return std::pair<std::string, std::string>(getHash, getSalt);
}

std::map<int, std::string> ChatDatabase::getRoomUsers(const std::string& room_name, const int limit) const
{
    if (isConnected() == false) return std::map<int, std::string>();      

    std::string safe_room = escapeString(room_name);
    std::string sql = "SELECT user_id, nickname FROM room_members WHERE room_name = '" + room_name + "' LIMIT " + std::to_string(limit);
    
    PGresult* result_request = executeQueryWithResult(sql);
    std::map<int, std::string> result;
    for (size_t i = 0; i < PQntuples(result_request); i++)
    {
        std::string getUserId = PQgetvalue(result_request, i, 0);
        std::string getNickname = PQgetvalue(result_request, i, 1);
        result[std::stoi(getUserId)] = getNickname;
    }  

    PQclear(result_request);

    return result;
}

bool ChatDatabase::savePrivateMessage(const int from_user, const int to_user, const std::string& message)
{
    if (isConnected() == false) return false;

    std::string safe_msg = escapeString(message);
    std::string sql = "INSERT INTO messages (from_user, to_user, message) VALUES (" 
                        + std::to_string(from_user) + ", " 
                        + std::to_string(to_user) + ", '" 
                        + safe_msg + "')";

    return executeQuery(sql);
}

std::vector<std::string> ChatDatabase::getPrivateMessages(const int user1, const int user2, const int limit) const
{
    if (isConnected() == false) return std::vector<std::string>();

    std::string sql = "SELECT * FROM messages WHERE (from_user = " + std::to_string(user1) 
                  + " AND to_user = " + std::to_string(user2) + ") OR (from_user = " 
                  + std::to_string(user2) + " AND to_user = " + std::to_string(user1) 
                  + ") ORDER BY created_at DESC LIMIT " + std::to_string(limit);

    PGresult* result_request = executeQueryWithResult(sql);

    if (result_request == nullptr) return std::vector<std::string>();
    std::vector<std::string> result;
    int rows = PQntuples(result_request);

    for (size_t i = 0; i < rows; i++)
    {
        std::string message = PQgetvalue(result_request, i, 3);
        result.push_back(message);
    }

    PQclear(result_request);

    return result;
}
