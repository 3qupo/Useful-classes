#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

class AuthManager
{
private:
    std::unordered_map<std::string, std::string> _cashe;

public:
    AuthManager();

    bool registerUser(const std::string& password, const std::string& login);
    bool autenticate(const std::string& password, const std::string& login);
    bool changePassword(const std::string& old_password, const std::string& new_password);
};
