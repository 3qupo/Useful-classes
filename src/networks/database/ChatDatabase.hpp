#pragma once

#include <string>
#include <iostream>
#include <postgresql/libpq-fe.h>  
#include <map>
#include <set>
#include "Database.hpp"

class ChatDatabase : public Database
{
private:
    std::string message_;
    size_t count_clients_;
    std::set<std::string> users_;

    
public:
    ChatDatabase();
    ~ChatDatabase();
};

