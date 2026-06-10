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
    std::string input;
    while (true)
    {
        std::cout << "You: ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "q" || input == "z" || input == "quit") break;

        client.sendMessage(input);
        std::string reply = client.receiveMessage();
        std::cout << "Server: " << reply << std::endl;
    }
    
    client.closeClient();
    return 0;
}