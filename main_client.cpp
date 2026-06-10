#include "include/networks/EchoClient.hpp"
#include <iostream>

int main() {
    std::cout << "Starting Echo Client..." << std::endl;
    
    // Подключаемся к серверу (localhost, порт 8080)
    EchoClient client("127.0.0.1", 8080);
    
    if (!client.connectServer()) {
        std::cerr << "Failed to connect to server" << std::endl;
        return 1;
    }
    
    std::cout << "Connected to server!" << std::endl;
    
    // Отправляем сообщение
    std::string message = "What's up, bro";
    std::cout << "Sending: " << message << std::endl;
    client.sendMessage(message);
    
    // Получаем ответ
    std::string reply = client.receiveMessage();
    std::cout << "Received: " << reply << std::endl;
    
    client.closeClient();
    return 0;
}