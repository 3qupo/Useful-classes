#include "Database.hpp"
#include <string>
#include <iostream>

// Connection status: CONNECTION_OK

Database::Database() 
{
    _connection = nullptr;
    _isConnected = false;
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
    std::cout << "Подлючение к БД: " << _dbname.c_str() << std::endl;
    _connection = PQsetdbLogin( _host.c_str(),
                                _port.c_str(),
                                nullptr,
                                nullptr,
                                _dbname.c_str(),
                                _user.c_str(),
                                _password.c_str());

    _isConnected = (PQstatus(_connection) == CONNECTION_OK);
    std::cout << "БД подключена!" << std::endl;
    return _isConnected;
}

void Database::disconnect()
{
    if (_connection) 
    {
        PQfinish(_connection);
        _connection = nullptr;
        _isConnected = false;
    }
}

bool Database::isConnected() const { return _isConnected; }

bool Database::executeQuery(const std::string& sql)
{
    
    return false;
}