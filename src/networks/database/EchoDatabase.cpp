#include <string>
#include <iostream>
#include "EchoDatabase.hpp"
#include "Database.hpp"
#include <vector>


EchoDatabase::EchoDatabase()
{
    _tableName = "EchoServer";
}

bool EchoDatabase::logMessage(const std::string& client_id, const std::string& message)
{
    std::string excape_client_id = escapeString(client_id);
    std::string excape_message = escapeString(message);

    std::string sql_command = "INSERT INTO echo_logs (client_ip , message) VALUES (" + excape_client_id + ", " + excape_message + ")";
    bool result = executeQuery(sql_command);
    if (result == true) return true;
    else return false;
}

std::vector<std::string> EchoDatabase::getRecentMessage(const int limit)
{
    std::string sql_command = "SELECT message FROM echo_logs ORDER BY created_at DESC LIMIT " + std::to_string(limit);
    PGresult* result = executeQueryWithResult(sql_command);

    if (result == nullptr) return {};

    int rows = PQntuples(result);
    std::vector<std::string> messages;

    for(int i = 0; i < rows; i++)
    {
        char* value = PQgetvalue(result, i, 0);
        messages.push_back(value ? value : "");
    }

    PQclear(result);

    return messages;
}