#include "Database.hpp"
#include <string>
#include <iostream>

// Success connection status: CONNECTION_OK

Database::Database() 
{
    _connection = nullptr;
    _isConnected = false;
    _lastError = "";
}

Database::~Database() 
{ 
    disconnect(); 
    std::cout << "БД " << _dbname.c_str() << "отключена!" << std::endl;
}

bool Database::connect(const std::string& _host,
                       const std::string& _port,
                       const std::string& _dbname,
                       const std::string& _user,
                       const std::string& _password)
{
    if (_isConnected || _connection) 
    {
        _lastError = "Already connected to database\n";
        return false;
    }

    std::cout << "Подключение к БД: " << _dbname.c_str() << std::endl;
    _connection = PQsetdbLogin( _host.c_str(),
                                _port.c_str(),
                                nullptr,
                                nullptr,
                                _dbname.c_str(),
                                _user.c_str(),
                                _password.c_str());

    _isConnected = (PQstatus(_connection) == CONNECTION_OK);

    if(!_isConnected)
    {
        _lastError = PQerrorMessage(_connection);
        PQfinish(_connection);
        _connection = nullptr;
        return false;
    }

    std::cout << "БД подключена!" << std::endl;
    _lastError = "";

    return _isConnected;
}

void Database::disconnect()
{
    if (_connection) 
    {
        PQfinish(_connection);
        _connection = nullptr;
        _isConnected = false;
        _lastError = "";
    }
}

bool Database::isConnected() const { return _isConnected; }

bool Database::executeQuery(const std::string& sql)
{
    if (!_isConnected || _connection == nullptr) 
    {   
        _lastError = "Not connected to database\n";
        return false;
    }
    
    PGresult* res = PQexec(_connection, sql.c_str());

    ExecStatusType status = PQresultStatus(res);

    if(status != PGRES_COMMAND_OK)
    {
        _lastError = PQerrorMessage(_connection);
        PQclear(res);
        return false;
    }

    PQclear(res);
    _lastError = "";

    return true;
}

std::string Database::getLastError() const
{
    return _lastError;
}

std::string Database::escapeString(const std::string& str)
{
    if (!_isConnected || _connection == nullptr) 
    {   
        _lastError = "Not connected to database\n";
        return "";
    }

    char* result = PQescapeLiteral(_connection, str.c_str(), str.length());
    if (result == nullptr) 
    {   
        _lastError = PQerrorMessage(_connection);
        return "";
    }

    std::string escaped = result;
    PQfreemem(result);
    _lastError = "";

    return escaped;
}

PGresult* Database::executeQueryWithResult(const std::string& sql)
{
    if (!_isConnected || _connection == nullptr) 
    {   
        _lastError = "Not connected to database\n";
        return nullptr;
    }

    PGresult* request = PQexec(_connection, sql.c_str());

    ExecStatusType status = PQresultStatus(request);
    if(status != PGRES_TUPLES_OK) 
    {
        _lastError = PQerrorMessage(_connection);
        PQclear(request);
        return nullptr;
    }
    
    _lastError = "";

    return request;
}