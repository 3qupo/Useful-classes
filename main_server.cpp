#include "include/networks/EchoServer.hpp"
#include <iostream>
    
int main() {
    std::cout << "Starting Echo Server..." << std::endl;
    
    // Создаём сервер на порту 8080
    EchoServer server(8080);
    
    // Запускаем сервер (будет работать до Ctrl+C)
    server.start();
    
    std::cout << "Server shutdown complete" << std::endl;
    return 0;
}