#include <iostream>
#include <string>
#include <unordered_map>
#include "AuthManager.hpp"
#include "../../../include/algoritms/sha256.hpp"
#include "../database/ChatDatabase.hpp"
#include <openssl/evp.h>
#include <openssl/err.h>
#include <random>

AuthManager::AuthManager(ChatDatabase& database)
{
    _db = database;
}

bool AuthManager::registerUser(const std::string& password, const std::string& login)
{
    if (_db.isConnected() == false) return false;
    
    auto result = _db.getUserHash(login);
    if (!result.first.empty()) return false;

    std::string salt = generateSalt();
    std::string hash = hashPassword(password, salt);
    _db.createUser(login, hash, salt);
    _cashe[login] = hash;

    return true;
}

bool AuthManager::authenticate(const std::string& password, const std::string& login)
{
    if (_db.isConnected() == false) return false;
    if (_cashe[password] == login) return true; 
    
    auto result = _db.getUserHash(login);
    if (!result.first.empty()) return false;

    std::string hash = result.first;
    std::string salt = result.second;

    std::string hash2 = hashPassword(password, salt);
    if (hash != hash2) return false;

    return true;
}

bool AuthManager::changePassword(const std::string& login, const std::string& old_password, const std::string& new_password)
{
    if (_db.isConnected() == false) return false;
    auto result = _db.getUserHash(login);
    if (!result.first.empty()) return false;

}

std::string AuthManager::generateSalt()
{
    size_t length = 16;
    std::string salt(length, '\0');
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dis(0, 255);
    
    for (size_t i = 0; i < length; i++)
    {
        salt[i] = static_cast<char>(dis(gen));
    }

    return salt;
}   

std::string AuthManager::hashPassword(const std::string& password, const std::string& salt)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX context;

    SHA256_Init(&context);
    SHA256_Update(&context, password.c_str(), password.size());
    SHA256_Update(&context, salt.data(), salt.size()); 
    SHA256_Final(hash, &context);

    std::string output;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) 
    {
        char buf[3];
        snprintf(buf, sizeof(buf), "%02x", hash[i]);
        output += buf;
    }

    return output;
}