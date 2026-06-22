#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

class AuthManager
{
private:
    std::unordered_map<std::string, std::string> _cashe;
    ChatDatabase* _db;

    std::string generateSalt(const std::string& login);
    std::string hashPassword(const std::string& password, const std::string& salt);

public:
    AuthManager();

    bool registerUser(const std::string& password, const std::string& login);
    bool authenticate(const std::string& password, const std::string& login);
    bool changePassword(const std::string& login, const std::string& old_password, const std::string& new_password);
};
