#pragma once

#include <string>
#include <iostream>
#include "Database.hpp"
#include <postgresql/libpq-fe.h>
#include <vector>

class EchoDatabase : public Database
{
private:
    std::string _tableName;
public:
    EchoDatabase();

    bool logMessage(const std::string& client_id, const std::string& message);
    std::vector<std::string> getRecentMessage(const int limit);
};
