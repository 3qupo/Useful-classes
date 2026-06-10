g++ -o echo_server ../main_server.cpp networks/EchoServer.cpp networks/database/Database.cpp networks/database/EchoDatabase.cpp -lpq
g++ -o echo_client ../main_client.cpp networks/EchoClient.cpp -lpq

