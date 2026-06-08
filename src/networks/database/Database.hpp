
#include <postgresql/libpq-fe.h>  
#include <string>

class Database
{
private:
    PGconn* _connection;
    std::string _host;
    std::string _port;
    std::string _dbname;
    std::string _user;
    std::string _password;
    bool _isConnected;
    std::string _lastError;

public:
    Database();
    ~Database();

    bool connect(const std::string& _host,
                const std::string& _port,
                const std::string& _dbname,
                const std::string& _user,
                const std::string& _password);                      // Установление соединения
    void disconnect();                                              // Закрытие соединения
    bool isConnected() const;                                       // Возвращение статуса подключения
    bool executeQuery(const std::string& sql);                      // Выполнение SQL-запроса (INSERT, UPDATE, DELETE, CREATE)
    PGresult* executeQueryWithResult(const std::string& sql);       // Выполнение SELECT и возвращение результата
    std::string escapeString(const std::string& str);               // Экранирование строки (защита от SQL-инъекций)
    std::string getLastError() const;                               // Возврат последней ошибки
};

